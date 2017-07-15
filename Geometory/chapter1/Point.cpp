#define X 0
#define Y 1
typedef enum {FALSE, TRUE} bool;

#define DIM 2
typedef int tPointi[DIM];

typedef struct tVertexStructure tsVertex;
typedef tsVertex* tVertex;
struct tVertexStructure {
  // Index
  int vnum;
  // Coordinates
  // TRUE iff an ear
  tPointi v;
  bool ear;
  tVertex next, prev;
};

// use circular list to represent a polygon
tVertex vertices = NULL;

void tranverse() {
  tVertex v;
  v = vertices;
  do {
    // process vertex
    v = v->next;
  } 
  // != the head of circular list
  while (v !=
  vertices);
}

// '\' for connet the next line
#define NEW(p, type) \
// FIXME:
if ((p=(type *)malloc (sizeof(type))) == NULL) {\
printf("NEW: Out of Memeory!\n");\
// FIXME:
exit(EXIT FAILURE); // same as exit(1), but the latter is magic number
}
// FIXME:\
#define ADD(head, p) \
if(head) {\
p->next = head;\
p->prev = head->prev;\
head->prev->next = p;\
head->prev = p;\
}\
else {\
head = p;\
head->next = head->prev = head;
}

// TODO: another area computation
// Area part
int AreaTri(tPointi a, tPointi b, tPointi c) {
  // may cause integer overflow
  return (b[X] - a[X])*(c[Y] - a[Y]) - (c[X] - a[X])*(b[Y] - a[Y]);
}

// use fan-calculation
int AreaPoly() {
  int sum = 0;
  tVertex p, a;

  p = vertices;
  a = p->next;
  do {
    sum += AreaTri(p->v, a->v, a->next->v);
    a = a->next;
  } while (a->next != p);
  return sum;
}

