#include "../include/mesh.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static void mesh_compute_normals(Mesh *m){
    for (int i = 0; i < m->nverts; i++) m->verts[i].normal = v3(0,0,0);
    for (int i = 0; i < m->nindices; i += 3){
        Vertex *a = &m->verts[m->indices[i+0]];
        Vertex *b = &m->verts[m->indices[i+1]];
        Vertex *c = &m->verts[m->indices[i+2]];
        Vec3 n = v3_cross(v3_sub(b->pos, a->pos), v3_sub(c->pos, a->pos));
        a->normal = v3_add(a->normal, n);
        b->normal = v3_add(b->normal, n);
        c->normal = v3_add(c->normal, n);
    }
    for (int i = 0; i < m->nverts; i++)
        m->verts[i].normal = v3_norm(m->verts[i].normal);
}

void mesh_free(Mesh *m){
    free(m->verts); free(m->indices);
    m->verts = NULL; m->indices = NULL;
    m->nverts = m->nindices = 0;
}

Mesh load_obj(const char *path){
    Mesh mesh = {0};
    FILE *f = fopen(path, "r");
    if (!f){ fprintf(stderr, "Failed to open %s\n", path); return mesh; }

    Vec3 *positions = NULL; int npos = 0, cap_pos = 0;
    Vec3 *normals   = NULL; int nnorm = 0, cap_norm = 0;

    char line[512];
    while (fgets(line, sizeof(line), f)){
        char *p = line;
        while (*p == ' ' || *p == '\t') p++;

        if (p[0] == 'v' && p[1] == ' '){
            Vec3 v;
            if (sscanf(p+2, "%f %f %f", &v.x, &v.y, &v.z) == 3){
                if (npos == cap_pos){ cap_pos = cap_pos ? cap_pos*2 : 1024;
                    positions = realloc(positions, cap_pos * sizeof(Vec3)); }
                positions[npos++] = v;
            }
        } else if (p[0] == 'v' && p[1] == 'n' && p[2] == ' '){
            Vec3 v;
            if (sscanf(p+3, "%f %f %f", &v.x, &v.y, &v.z) == 3){
                if (nnorm == cap_norm){ cap_norm = cap_norm ? cap_norm*2 : 1024;
                    normals = realloc(normals, cap_norm * sizeof(Vec3)); }
                normals[nnorm++] = v;
            }
        } else if (p[0] == 'f' && p[1] == ' '){
            int idx[3] = {-1,-1,-1};
            int nidx[3] = {-1,-1,-1};
            int got = 0;
            char *tok = strtok(p+2, " \t\r\n");
            while (tok && got < 3){
                int vi = 0, ti = 0, ni = 0;
                if (sscanf(tok, "%d/%d/%d", &vi, &ti, &ni) >= 1){
                } else if (sscanf(tok, "%d//%d", &vi, &ni) == 2){
                } else if (sscanf(tok, "%d/%d", &vi, &ti) == 2){
                } else if (sscanf(tok, "%d", &vi) == 1){
                } else {
                    tok = strtok(NULL, " \t\r\n"); continue;
                }
                if (vi < 0) vi = npos + vi + 1;
                if (ni < 0) ni = nnorm + ni + 1;
                idx[got]  = vi - 1;
                nidx[got] = ni - 1;
                got++;
                tok = strtok(NULL, " \t\r\n");
            }
            if (got == 3){
                for (int c = 0; c < 3; c++){
                    mesh.verts = realloc(mesh.verts, (mesh.nverts+1) * sizeof(Vertex));
                    Vertex *vx = &mesh.verts[mesh.nverts];
                    vx->pos = (idx[c] >= 0 && idx[c] < npos) ? positions[idx[c]] : v3(0,0,0);
                    vx->normal = (nidx[c] >= 0 && nidx[c] < nnorm)
                                 ? normals[nidx[c]] : v3(0,0,0);
                    mesh.indices = realloc(mesh.indices, (mesh.nindices+1) * sizeof(uint32_t));
                    mesh.indices[mesh.nindices++] = mesh.nverts;
                    mesh.nverts++;
                }
            }
        }
    }
    fclose(f);
    free(positions); free(normals);

    bool any_normal = false;
    for (int i = 0; i < mesh.nverts; i++)
        if (v3_len(mesh.verts[i].normal) > 1e-6f) { any_normal = true; break; }
    if (!any_normal) mesh_compute_normals(&mesh);

    if (mesh.nverts > 0){
        Vec3 mn = mesh.verts[0].pos, mx = mesh.verts[0].pos;
        for (int i = 1; i < mesh.nverts; i++){
            Vec3 p = mesh.verts[i].pos;
            if (p.x < mn.x) mn.x = p.x; if (p.x > mx.x) mx.x = p.x;
            if (p.y < mn.y) mn.y = p.y; if (p.y > mx.y) mx.y = p.y;
            if (p.z < mn.z) mn.z = p.z; if (p.z > mx.z) mx.z = p.z;
        }
        Vec3 c = v3_scale(v3_add(mn, mx), 0.5f);
        float r = 0;
        for (int i = 0; i < mesh.nverts; i++){
            Vec3 p = v3_sub(mesh.verts[i].pos, c);
            if (v3_len(p) > r) r = v3_len(p);
        }
        float s = (r > 1e-6f) ? (1.0f / r) : 1.0f;
        for (int i = 0; i < mesh.nverts; i++)
            mesh.verts[i].pos = v3_scale(v3_sub(mesh.verts[i].pos, c), s);
    }
    return mesh;
}
