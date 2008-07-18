#ifndef BTOREXP_H_INCLUDED
#define BTOREXP_H_INCLUDED

#include "boolector.h"
#include "btoraigvec.h"
#include "btorhash.h"
#include "btormem.h"
#include "btorqueue.h"
#include "btorstack.h"

/*------------------------------------------------------------------------*/
/* PRIVATE INTERFACE                                                      */
/*------------------------------------------------------------------------*/

BTOR_DECLARE_STACK (ExpPtr, BtorExp *);

BTOR_DECLARE_QUEUE (ExpPtr, BtorExp *);

/* NOTE: DO NOT REORDER THE INDICES.
 * CERTAIN MACROS DEPEND ON ORDER.
 */
enum BtorExpKind
{
  /* Even though the following is just for debugging purposes,
   * we should not put '#ifndef NDEBUG' around.  This would
   * make delta debugging of Heisenbugs in release mode more
   * difficult.
   */
  BTOR_INVALID_EXP = 0,

  BTOR_CONST_EXP  = 1,
  BTOR_VAR_EXP    = 2,
  BTOR_ARRAY_EXP  = 3,
  BTOR_SLICE_EXP  = 4,
  BTOR_AND_EXP    = 5,
  BTOR_BEQ_EXP    = 6, /* equality on bit vectors */
  BTOR_AEQ_EXP    = 7, /* equality on arrays */
  BTOR_ADD_EXP    = 8,
  BTOR_MUL_EXP    = 9,
  BTOR_ULT_EXP    = 10,
  BTOR_SLL_EXP    = 11,
  BTOR_SRL_EXP    = 12,
  BTOR_UDIV_EXP   = 13,
  BTOR_UREM_EXP   = 14,
  BTOR_CONCAT_EXP = 15,
  BTOR_READ_EXP   = 16,
  BTOR_WRITE_EXP  = 17,
  BTOR_BCOND_EXP  = 18, /* conditional on bit vectors */
  BTOR_ACOND_EXP  = 19, /* conditional on arrays */
  BTOR_PROXY_EXP  = 20, /* simplified expression without children */
};

typedef enum BtorExpKind BtorExpKind;

typedef struct BtorExpPair BtorExpPair;

#define BTOR_BV_VAR_EXP                                                      \
  struct                                                                     \
  {                                                                          \
    BtorExpKind kind : 5;        /* kind of expression */                    \
    unsigned int mark : 3;       /* for DAG traversal */                     \
    unsigned int array_mark : 3; /* for bottom up array traversal */         \
    unsigned int aux_mark : 3;   /* auxiallary mark flag */                  \
    unsigned int reachable : 1;  /* flag determines if expression            \
                                    is reachable from root */                \
    unsigned int                                                             \
        sat_both_phases : 1;       /* flag determines if expression has been \
                                      encoded into SAT in both phases */     \
    unsigned int vread : 1;        /* flag determines if expression          \
                                      is a virtual read */                   \
    unsigned int constraint : 1;   /* flag determines if expression is a     \
                                      top level constraint */                \
    unsigned int erased : 1;       /* for debugging purposes */              \
    unsigned int disconnected : 1; /* for debugging purposes */              \
    unsigned int unique : 1;       /* in unique table? */                    \
    unsigned int bytes : 8;        /* allocated bytes */                     \
    unsigned int arity : 2;        /* arity of operator */                   \
    char *bits;                    /* three valued bits */                   \
    int id;                        /* unique expression id */                \
    int len;                       /* number of bits */                      \
    unsigned int refs;             /* reference counter */                   \
    union                                                                    \
    {                                                                        \
      BtorAIGVec *av;        /* synthesized AIG vector */                    \
      BtorPtrHashTable *rho; /* used for finding array conflicts */          \
    };                                                                       \
    struct BtorExp *next;         /* next element in unique table */         \
    struct BtorExp *parent;       /* parent pointer for BFS */               \
    struct BtorExp *simplified;   /* equivalent simplified expression */     \
    Btor *btor;                   /* boolector */                            \
    struct BtorExp *first_parent; /* head of parent list */                  \
    struct BtorExp *last_parent;  /* tail of parent list */                  \
  }

#define BTOR_BV_ADDITIONAL_EXP                                               \
  struct                                                                     \
  {                                                                          \
    union                                                                    \
    {                                                                        \
      struct                                                                 \
      {                                                                      \
        char *symbol; /* symbol of variables for output */                   \
        int upper;    /* upper index for slices */                           \
        union                                                                \
        {                                                                    \
          int lower;           /* lower index for slices */                  \
          BtorExpPair *vreads; /* virtual reads for array equalites */       \
        };                                                                   \
      };                                                                     \
      struct BtorExp *e[3]; /* three expression children */                  \
    };                                                                       \
    struct BtorExp *prev_parent[3]; /* prev exp in parent list of child i */ \
    struct BtorExp *next_parent[3]; /* next exp in parent list of child i */ \
  }

#define BTOR_ARRAY_VAR_EXP                                                   \
  struct                                                                     \
  {                                                                          \
    int index_len;                          /* length of the index */        \
    struct BtorExp *first_aeq_acond_parent; /* first array equality or array \
                                               conditional in parent list */ \
    struct BtorExp *last_aeq_acond_parent;  /* last array equality or array  \
                                               conditional in parent list */ \
  }

#define BTOR_ARRAY_ADDITIONAL_EXP                                          \
  struct                                                                   \
  {                                                                        \
    struct BtorExp *prev_aeq_acond_parent[3]; /* prev array equality or    \
                                                 conditional in aeq acond  \
                                                 parent list of child i */ \
    struct BtorExp *next_aeq_acond_parent[3]; /* next array equality or    \
                                                 conditional in aeq acond  \
                                                 parent list of child i */ \
  }

struct BtorBVVarExp
{
  BTOR_BV_VAR_EXP;
  char *symbol;
};

typedef struct BtorBVVarExp BtorBVVarExp;

struct BtorBVConstExp
{
  BTOR_BV_VAR_EXP;
};

typedef struct BtorBVConstExp BtorBVConstExp;

struct BtorBVExp
{
  BTOR_BV_VAR_EXP;
  BTOR_BV_ADDITIONAL_EXP;
};

typedef struct BtorBVExp BtorBVExp;

struct BtorArrayVarExp
{
  BTOR_BV_VAR_EXP;
  BTOR_BV_ADDITIONAL_EXP;
  BTOR_ARRAY_VAR_EXP;
};

typedef struct BtorArrayVarExp BtorArrayVarExp;

struct BtorExp
{
  BTOR_BV_VAR_EXP;
  BTOR_BV_ADDITIONAL_EXP;
  BTOR_ARRAY_VAR_EXP;
  BTOR_ARRAY_ADDITIONAL_EXP;
};

struct BtorExpUniqueTable
{
  int size;
  int num_elements;
  struct BtorExp **chains;
};

typedef struct BtorExpUniqueTable BtorExpUniqueTable;

struct ConstraintStats
{
  int varsubst;
  int embedded;
  int unsynthesized;
  int synthesized;
};

typedef struct ConstraintStats ConstraintStats;

struct Btor
{
  BtorMemMgr *mm;
  BtorExpUniqueTable table;
  BtorAIGVecMgr *avmgr;
  BtorPtrHashTable *arrays;
  int id; /* global expression id counter */
  int valid_assignments;
  int rewrite_level;
  int verbosity;
  int has_array_equalities;
  int replay;
  int vread_index_id;
  int inconsistent;
  BtorPtrHashTable *exp_pair_cnf_diff_id_table; /* hash table for CNF ids */
  BtorPtrHashTable *exp_pair_cnf_eq_id_table;   /* hash table for CNF ids */
  BtorPtrHashTable *varsubst_constraints;
  BtorPtrHashTable *embedded_constraints;
  BtorPtrHashTable *unsynthesized_constraints;
  BtorPtrHashTable *synthesized_constraints;
  BtorPtrHashTable *assumptions;
  BtorExpPtrStack replay_constraints;
  /* statistics */
  struct
  {
    /* number of iterative refinements */
    int refinements;
    /* number of restarts as a result of lazy synthesis */
    int synthesis_assignment_inconsistencies;
    /* number of array axiom 1 conflicts:
     * a = b /\ i = j => read(a, i) = read(b, j) */
    int array_axiom_1_conflicts;
    /* number of array axiom 2 conflicts:
     * i = j => read(write(a, i, e), j) = e */
    int array_axiom_2_conflicts;
    /* number of variables that have been substituted */
    int var_substitutions;
    /* number of array variables that have been substituted */
    int array_substitutions;
    /* embedded constraint substitutions */
    int ec_substitutions;
    /* number of virtual reads */
    int vreads;
    /* number of linear equations */
    int linear_equations;
    /* number of add chains normalizations */
    int adds_normalized;
    /* number of mul chains normalizations */
    int muls_normalized;
    /* number of simplifications as result of 3 valued logic analysis */
    int simplifications_3vl;
    /*  how often have we pushed a read over write during construction */
    int read_props_construct;
    /* sum of the size of all added lemmas */
    long long int lemmas_size_sum;
    /* sum of the size of all linking clauses */
    long long int lclause_size_sum;
    /* constraint statistics */
    ConstraintStats constraints;
    struct
    {
      ConstraintStats constraints;
    } old;
    long long expressions;
  } stats;
};

#define BTOR_IS_CONST_EXP_KIND(kind) ((kind) == BTOR_CONST_EXP)
#define BTOR_IS_VAR_EXP_KIND(kind) ((kind) == BTOR_VAR_EXP)
#define BTOR_IS_READ_EXP_KIND(kind) (kind == BTOR_READ_EXP)
#define BTOR_IS_WRITE_EXP_KIND(kind) (kind == BTOR_WRITE_EXP)
#define BTOR_IS_ARRAY_COND_EXP_KIND(kind) (kind == BTOR_ACOND_EXP)
#define BTOR_IS_PROXY_EXP_KIND(kind) ((kind) == BTOR_PROXY_EXP)
#define BTOR_IS_BV_COND_EXP_KIND(kind) (kind == BTOR_BCOND_EXP)
#define BTOR_IS_ATOMIC_ARRAY_EXP_KIND(kind) (kind == BTOR_ARRAY_EXP)
#define BTOR_IS_ARRAY_EXP_KIND(kind)                        \
  (((kind) == BTOR_ARRAY_EXP) || ((kind) == BTOR_WRITE_EXP) \
   || ((kind) == BTOR_ACOND_EXP))
#define BTOR_IS_ARRAY_EQ_EXP_KIND(kind) (kind == BTOR_AEQ_EXP)
#define BTOR_IS_BV_EQ_EXP_KIND(kind) (kind == BTOR_BEQ_EXP)
#define BTOR_IS_UNARY_EXP_KIND(kind) ((kind) == BTOR_SLICE_EXP)
#define BTOR_IS_BINARY_EXP_KIND(kind) \
  (((kind) >= BTOR_AND_EXP) && ((kind) <= BTOR_READ_EXP))
#define BTOR_IS_BINARY_COMMUTATIVE_EXP_KIND(kind) \
  (((kind) >= BTOR_AND_EXP) && ((kind) <= BTOR_MUL_EXP))
#define BTOR_IS_TERNARY_EXP_KIND(kind) \
  (((kind) >= BTOR_WRITE_EXP) && ((kind) <= BTOR_ACOND_EXP))

#define BTOR_IS_CONST_EXP(exp) (BTOR_IS_CONST_EXP_KIND ((exp)->kind))
#define BTOR_IS_VAR_EXP(exp) (BTOR_IS_VAR_EXP_KIND ((exp)->kind))
#define BTOR_IS_READ_EXP(exp) (BTOR_IS_READ_EXP_KIND ((exp)->kind))
#define BTOR_IS_WRITE_EXP(exp) (BTOR_IS_WRITE_EXP_KIND ((exp)->kind))
#define BTOR_IS_ARRAY_COND_EXP(exp) (BTOR_IS_ARRAY_COND_EXP_KIND ((exp)->kind))
#define BTOR_IS_BV_COND_EXP(exp) (BTOR_IS_BV_COND_EXP_KIND ((exp)->kind))
#define BTOR_IS_PROXY_EXP(exp) (BTOR_IS_PROXY_EXP_KIND ((exp)->kind))
#define BTOR_IS_ARRAY_OR_BV_COND_EXP(exp) \
  (BTOR_IS_ARRAY_COND_EXP (exp) || BTOR_IS_BV_COND_EXP (exp))
#define BTOR_IS_ATOMIC_ARRAY_EXP(exp) \
  (BTOR_IS_ATOMIC_ARRAY_EXP_KIND ((exp)->kind))
#define BTOR_IS_ARRAY_EXP(exp) (BTOR_IS_ARRAY_EXP_KIND ((exp)->kind))
#define BTOR_IS_ARRAY_EQ_EXP(exp) (BTOR_IS_ARRAY_EQ_EXP_KIND ((exp)->kind))
#define BTOR_IS_BV_EQ_EXP(exp) (BTOR_IS_BV_EQ_EXP_KIND ((exp)->kind))
#define BTOR_IS_ARRAY_OR_BV_EQ_EXP(exp) \
  (BTOR_IS_ARRAY_EQ_EXP (exp) || BTOR_IS_BV_EQ_EXP (exp))
#define BTOR_IS_UNARY_EXP(exp) (BTOR_IS_UNARY_EXP_KIND ((exp)->kind))
#define BTOR_IS_BINARY_EXP(exp) (BTOR_IS_BINARY_EXP_KIND ((exp)->kind))
#define BTOR_IS_TERNARY_EXP(exp) (BTOR_IS_TERNARY_EXP_KIND ((exp)->kind))

#define BTOR_INVERT_EXP(exp) ((BtorExp *) (1ul ^ (unsigned long int) (exp)))
#define BTOR_IS_INVERTED_EXP(exp) (1ul & (unsigned long int) (exp))
#define BTOR_COND_INVERT_EXP(cond_exp, exp)           \
  ((BtorExp *) (((unsigned long int) (cond_exp) &1ul) \
                ^ (unsigned long int) (exp)))
#define BTOR_GET_ID_EXP(exp) \
  (BTOR_IS_INVERTED_EXP (exp) ? -BTOR_REAL_ADDR_EXP (exp)->id : exp->id)
#define BTOR_AIGVEC_EXP(btor, exp)                                     \
  (BTOR_IS_INVERTED_EXP (exp)                                          \
       ? btor_not_aigvec ((btor)->avmgr, BTOR_REAL_ADDR_EXP (exp)->av) \
       : btor_copy_aigvec ((btor)->avmgr, exp->av))
#define BTOR_BITS_EXP(mm, exp)                               \
  (BTOR_IS_INVERTED_EXP (exp)                                \
       ? btor_not_const (mm, BTOR_REAL_ADDR_EXP (exp)->bits) \
       : btor_copy_const (mm, exp->bits))

#define BTOR_TAG_EXP(exp, tag) \
  ((BtorExp *) ((unsigned long int) tag | (unsigned long int) (exp)))
#define BTOR_GET_TAG_EXP(exp) ((int) (3ul & (unsigned long int) (exp)))
#define BTOR_REAL_ADDR_EXP(exp) ((BtorExp *) (~3ul & (unsigned long int) (exp)))
#define BTOR_IS_REGULAR_EXP(exp) (!(3ul & (unsigned long int) (exp)))

#define BTOR_IS_ACC_EXP(exp) (BTOR_IS_READ_EXP (exp) || BTOR_IS_WRITE_EXP (exp))
#define BTOR_GET_INDEX_ACC_EXP(exp) ((exp)->e[1])
#define BTOR_GET_VALUE_ACC_EXP(exp) \
  (BTOR_IS_READ_EXP (exp) ? (exp) : (exp)->e[2])
#define BTOR_ACC_TARGET_EXP(exp) (BTOR_IS_READ_EXP (exp) ? (exp)->e[0] : (exp))
#define BTOR_IS_SYNTH_EXP(exp) ((exp)->av != NULL)

/* Prints statistics */
void btor_print_stats_btor (Btor *btor);

/* Synthesizes formula represented by top
 * level constraints and assumptions to a single AIG.
 */
BtorAIG *btor_to_aig_exp (Btor *btor);

/* Synthesizes expression of arbitrary length to an AIG vector. Adds string
 * back annotation to the hash table, if the hash table is a non zero ptr.
 * The strings in 'data.asStr' are owned by the caller.  The hash table
 * is a map from AIG variables to strings.
 */
BtorAIGVec *btor_exp_to_aigvec (Btor *btor,
                                BtorExp *exp,
                                BtorPtrHashTable *table);

/* Translates formula represented by top level constraints
 * and assumptions into SAT instance.
 */
void btor_to_sat_exp (Btor *btor);

/* Marks all reachable expressions with new mark. */
void btor_mark_exp (Btor *btor, BtorExp *exp, int new_mark);

BtorExp *btor_next_exp_bmc (Btor *btor,
                            BtorPtrHashTable *reg_table,
                            BtorExp *root,
                            int k,
                            BtorPtrHashTable *input_table);

unsigned int btor_hash_exp_by_id (BtorExp *exp);

int btor_compare_exp_by_id (BtorExp *exp1, BtorExp *exp2);

#endif
