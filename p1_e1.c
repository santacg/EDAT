 #include <stdio.h>
 #include "vertex.h"
 

int main() {
    Vertex *v1 = NULL;
    Vertex *v2 = NULL;
    Vertex *v3 = NULL;
    
    /* Vertex initialization */
    v1 = vertex_init();
    if (!v1) return 1;
    v2 = vertex_init();
    if (!v2) {
        vertex_free(v1);
        return 1;
    }

    /* First vertex setting*/
    if(vertex_setId(v1, 10) == ERROR) {
        vertex_free(v1);
        vertex_free(v2);
        return 1;
    }
    if(vertex_setTag(v1, "one") == ERROR) {        
        vertex_free(v1);
        vertex_free(v2);
        return 1;
    }
    if(vertex_setState(v1, WHITE) == ERROR) {
        vertex_free(v1);
        vertex_free(v2);
        return 1;
    }
    
    /* Second vertex setting*/
    if (vertex_setId(v2, 20) == ERROR) {
        vertex_free(v1);
        vertex_free(v2);
        return 1;
    }
    if (vertex_setTag(v2, "two") == ERROR) {
        vertex_free(v1);
        vertex_free(v2);
        return 1;
    }
    if (vertex_setState(v2, BLACK) == ERROR) {
        vertex_free(v1);
        vertex_free(v2);
        return 1;
    }

    /* First vertex print */
    if (vertex_print(stdout, v1) == -1) {
        vertex_free(v1);
        vertex_free(v2);
        return 1;
    }
    /* Second vertex print */
    if (vertex_print(stdout, v2) == -1) {
        vertex_free(v1);
        vertex_free(v2);
        return 1;
    }
    /* Comparing vertices v1 and v2 */
    if (vertex_cmp(v1, v2) < 0) {
        fprintf(stdout, "\nv1 id or label is less than v2 id or label\n");
    }
    else if (vertex_cmp(v1, v2) > 0) {
        fprintf(stdout, "v1 id or label is greater than v2 id or label\n");
    }
    else if (vertex_cmp(v1, v2) == 0) {
        fprintf(stdout, "v1 id and/or label are/is equal to v2 id and/or label\n");
    }  
    else {
        vertex_free(v1);
        vertex_free(v2);
        return 1;  
    }

    /* Sencond vertex tag print */
    fprintf(stdout, "The tag of the second vertex is: ");
    fprintf(stdout, "%s\n", vertex_getTag(v2));

    /* Copy the first vertex  */
    v3 = vertex_copy(v1);
    if (!v3) {
        vertex_free(v1);
        vertex_free(v2);
        return 1;
    }

    /* Prints v1 and v3 ids to asure that v1 is copied in v3*/
    fprintf(stdout, "If v1 has been succsesfully copied, v3's id should be %ld \nVertex3 id is: %ld\n", vertex_getId(v1),  vertex_getId(v3));
    
    /* Print the first vertex */
    fprintf(stdout, "Vertex v1: ");
    if (vertex_print(stdout, v1) == -1) {
        vertex_free(v1);
        vertex_free(v2);
        vertex_free(v3);
        return 1;  
    }
    /* Print the third vertex */
    fprintf(stdout, "\nVertex v3: ");
    if (vertex_print(stdout, v3) == -1) {
        vertex_free(v1);
        vertex_free(v2);
        vertex_free(v3);
        return 1;
    }

    /* Comparing vertices v1 and v3 */
    if (vertex_cmp(v1, v3) < 0) {
        fprintf(stdout, "\nv1 id or label is less than v3 id or label\n");
    }
    else if (vertex_cmp(v1, v3) > 0) {
        fprintf(stdout, "\nv1 id or label is greater than v3 id or label\n");
    }
    else if (vertex_cmp(v1, v3) == 0) {
        fprintf(stdout, "\nv1 id and/or label are/is equal to v3 id and/or label\n");
    } 
    else {
        vertex_free(v1);
        vertex_free(v2);
        vertex_free(v3);
        return 1;
    }   

    vertex_free(v1);
    vertex_free(v2);
    vertex_free(v3);

    return 0;
}













