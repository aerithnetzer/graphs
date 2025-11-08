#include <igraph/igraph.h>
#include <stdatomic.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int readGraph(void) {
  igraph_t graph;
  igraph_real_t avg_path_len;
  igraph_int_t index = 0;
  const char *infilename = "graph.graphml";

  igraph_setup();

  igraph_set_attribute_table(&igraph_cattribute_table);
  FILE *infile = fopen("graph.graphml", "r");

  if (!infile) {
    fprintf(stderr, "Could not open input file '%s'.", infilename);
    exit(1);
  }

  igraph_error_handler_t *oldhandler =
      igraph_set_error_handler(igraph_error_handler_ignore);
  igraph_error_t ret = igraph_read_graph_graphml(&graph, infile, index);
  if (ret == IGRAPH_UNIMPLEMENTED) {
    fprintf(stderr, "igraph was compiled without GraphML support.");
    exit(77);
  }
  if (ret != IGRAPH_SUCCESS) {
    fprintf(stderr, "Unexpected error while reading GraphML.");
    exit(1);
  }
  igraph_set_error_handler(oldhandler);
  igraph_average_path_length(&graph, NULL, &avg_path_len, NULL,
                             IGRAPH_UNDIRECTED, /*unconn=*/true);

  printf("Average path length (randomized lattice): %g\n",
         (double)avg_path_len);
  return 0;
}

int myCustomGraph(void) {
  igraph_t graph;
  igraph_int_t vertex;
  vertex = 1;
  igraph_setup();
  return 0;
}

int weightedGraph(void) {
  igraph_t graph;
  igraph_vector_int_t dimvector;
  igraph_vector_int_t edges;
  igraph_real_t avg_path_len;
  igraph_vector_t expected_out_deg;
  igraph_vector_t expected_in_deg;
  igraph_bool_t loops;
  igraph_vector_t results;
  igraph_vs_t vs;
  igraph_real_t mean_degree;

  /*Set up the library*/
  igraph_setup();
  igraph_vector_int_init(&dimvector, 1);
  igraph_vector_init(&expected_out_deg, 500);
  igraph_vector_init(&expected_in_deg, 500);
  igraph_vector_init(&results, 0);
  int n = 100;
  for (int i = 0; i < n; i++) {
    VECTOR(expected_out_deg)[i] = 30;
    VECTOR(expected_in_deg)[i] = 30;
  }

  igraph_chung_lu_game(&graph, &expected_out_deg, &expected_in_deg, loops,
                       IGRAPH_CHUNG_LU_ORIGINAL);

  igraph_betweenness(&graph, /*weights=*/NULL, &results, igraph_vss_all(),
                     false, false);
  long m = igraph_vcount(&graph);
  printf("Num nodes in graph: %ld\n", m);
  long i = 0;
  for (i = 0; i < n; i++) {
    printf("Node %ld betweenness: %f\n", i, VECTOR(results)[i]);
  }

  igraph_mean_degree(&graph, &mean_degree, IGRAPH_LOOPS);
  printf("Average degree: %g\n", mean_degree);
  igraph_destroy(&graph);
  return 0;
}

int myFirstGraph(void) {
  igraph_t graph;                // Initializes a graph object.
  igraph_vector_int_t dimvector; // Initializes a vector array(?)
  igraph_vector_int_t edges;
  igraph_vector_bool_t periodic;
  igraph_real_t avg_path_len;

  igraph_setup(); // Initializes the library

  igraph_vector_int_init(&dimvector, 2); // This allocates a vector of size 2?
  VECTOR(dimvector)[0] = 30;
  VECTOR(dimvector)[1] = 30;

  igraph_vector_bool_init(&periodic, 2);
  igraph_vector_bool_fill(&periodic, true);
  igraph_square_lattice(&graph, &dimvector, 0, IGRAPH_UNDIRECTED,
                        /*mutual=*/false, &periodic);
  igraph_average_path_length(&graph, NULL, &avg_path_len, NULL,
                             IGRAPH_UNDIRECTED, /*unconn=*/true);
  printf("Average path length (lattice) = %g\n", (double)avg_path_len);

  igraph_rng_seed(igraph_rng_default(), 42);
  igraph_vector_int_init(&edges, 20);
  for (igraph_int_t i = 0; i < igraph_vector_int_size(&edges); i++) {
    VECTOR(edges)[i] = RNG_INTEGER(0, igraph_vcount(&graph) - 1);
  }

  igraph_add_edges(&graph, &edges, NULL);
  igraph_average_path_length(&graph, NULL, &avg_path_len, NULL,
                             IGRAPH_UNDIRECTED, /*unconn=*/true);
  printf("Average path length (randomized lattice): %g\n",
         (double)avg_path_len);

  return 0;
}

int gettingStarted(void) {
  igraph_int_t num_vertices = 10000;
  igraph_int_t num_edges = 100000;
  igraph_real_t diameter, mean_degree;
  igraph_t graph;

  igraph_setup();

  igraph_rng_seed(igraph_rng_default(), 42);

  igraph_erdos_renyi_game_gnm(&graph, num_vertices, num_edges,
                              IGRAPH_UNDIRECTED, IGRAPH_SIMPLE_SW,
                              IGRAPH_EDGE_UNLABELED);
  igraph_diameter(&graph, /* weights = */ NULL, &diameter,
                  /* from = */ NULL, /* to = */ NULL,
                  /* vertex_path = */ NULL, /* edge_path = */ NULL,
                  IGRAPH_UNDIRECTED, /* unconn= */ true);

  igraph_mean_degree(&graph, &mean_degree, IGRAPH_LOOPS);
  printf("Diameter of a random graph with average degree %g: %g\n", mean_degree,
         diameter);
  igraph_destroy(&graph);
  return 0;
}

int main(void) {
  readGraph();
  return 0;
}
