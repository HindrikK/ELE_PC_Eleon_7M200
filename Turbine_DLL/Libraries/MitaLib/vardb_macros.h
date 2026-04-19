/********************************************************************/
/*                                                                  */
/*            Copyright (c) 2003 Mita-Teknik a/s                    */
/*                                                                  */
/********************************************************************/
/*  $Date$
 *  $Author$
 *  $RCSfile$
 *  $Revision$ */
/********************************************************************/
/*                                                                  */
/* DESCRIPTION                                                      */
/*                                                                  */
/*     Macros to initilize VarDB variables                          */
/*                                                                  */
/* FUNCTIONS                                                        */
/*                                                                  */
/*     NA                                                           */
/*                                                                  */
/********************************************************************/

#ifndef __VARDB_MACROS_H__
#define __VARDB_MACROS_H__

#include "types.h"

#define ALIAS_MAGIC_NUMBER                     0x05A5A55A
#define VAR_MAGIC_NUMBER                       0xA55A5A50

/* Macro defining Parameters with Min and Max limits defined */ 
#define VAR_ELEMENT_PARAMETER(Name,Type,AccessRead,AccessWrite,ScaleType,ScaleValue,Unit,Precision,InitValue,MinValue,MaxValue,Lists) \
   {                                  \
   {VAR_MAGIC_NUMBER,     /* Magic number */          \
   0,                     /* Hash value */            \
   NULL,                  /* Next variable in index */\
   Name,                  /* Name */                  \
   Type,                  /* Type */                  \
   AccessRead,            /* AccessRead */            \
   AccessWrite,           /* AccessWrite */           \
   ScaleType,             /* ScaleType */             \
   ScaleValue,            /* ScaleValue */            \
   Unit,                  /* Unit */                  \
   Precision,             /* Precision */             \
 {(char *) InitValue},    /* Init value */            \
   0,                     /* Timestamp / Log flag */  \
   (scaletype_t)0,        /* DisplayScaleType */      \
   0,                     /* DisplayScaleValue */     \
   0,                     /* DisplayUnit */           \
   0,                     /* DisplayPrecision*/       \
   (enum update)PARAMETER,/* Update type */           \
   NULL,                  /* FirstSubscriber */       \
   NULL,                  /* PreviousVariable */      \
   NULL,                  /* NextVariable */          \
   0,                     /* ActiveReaders */         \
   0,                     /* OldValueBeingRead */     \
   0,                     /* TotalLogID */            \
   0},                    /* 5 min log ID */          \
  {NULL,                  /* Log flag parameter*/     \
 {(char *)MinValue},      /* Min. limit*/             \
 {(char *)MaxValue},      /* Max. limit*/             \
   Lists},                /* Selection list*/         \
   }

/* Macro defining Parameters with Min and Max limits defined */
#define VAR_ELEMENT_PARAMETER_F32(Name,AccessRead,AccessWrite,Unit,Precision,InitValue,MinValue,MaxValue,Lists) \
      {                                  \
      {VAR_MAGIC_NUMBER,     /* Magic number */          \
      0,                     /* Hash value */            \
      NULL,                  /* Next variable in index */\
      Name,                  /* Name */                  \
      TYPE_F32,              /* Type */                  \
      AccessRead,            /* AccessRead */            \
      AccessWrite,           /* AccessWrite */           \
      0,                     /* ScaleType */             \
      0,                     /* ScaleValue */            \
      Unit,                  /* Unit */                  \
      Precision,             /* Precision */             \
    {.f32 = InitValue},      /* Init value */            \
      0,                     /* Timestamp / Log flag */  \
      (scaletype_t)0,        /* DisplayScaleType */      \
      0,                     /* DisplayScaleValue */     \
      0,                     /* DisplayUnit */           \
      0,                     /* DisplayPrecision*/       \
      (enum update)PARAMETER,/* Update type */           \
      NULL,                  /* FirstSubscriber */       \
      NULL,                  /* PreviousVariable */      \
      NULL,                  /* NextVariable */          \
      0,                     /* ActiveReaders */         \
      0,                     /* OldValueBeingRead */     \
      0,                     /* TotalLogID */            \
      0},                    /* 5 min log ID */          \
     {NULL,                  /* Log flag parameter*/     \
    {.f32 = MinValue},       /* Min. limit*/             \
    {.f32 = MaxValue},       /* Max. limit*/             \
      Lists},                /* Selection list*/         \
      }
/* Macro defining Parameters with Min and Max limits defined */
#define VAR_ELEMENT_PARAMETER_F64(Name,AccessRead,AccessWrite,Unit,Precision,InitValue,MinValue,MaxValue,Lists) \
      {                                  \
      {VAR_MAGIC_NUMBER,     /* Magic number */          \
      0,                     /* Hash value */            \
      NULL,                  /* Next variable in index */\
      Name,                  /* Name */                  \
      TYPE_F64,              /* Type */                  \
      AccessRead,            /* AccessRead */            \
      AccessWrite,           /* AccessWrite */           \
      0,                     /* ScaleType */             \
      0,                     /* ScaleValue */            \
      Unit,                  /* Unit */                  \
      Precision,             /* Precision */             \
    {.f64 = InitValue},      /* Init value */            \
      0,                     /* Timestamp / Log flag */  \
      (scaletype_t)0,        /* DisplayScaleType */      \
      0,                     /* DisplayScaleValue */     \
      0,                     /* DisplayUnit */           \
      0,                     /* DisplayPrecision*/       \
      (enum update)PARAMETER,/* Update type */           \
      NULL,                  /* FirstSubscriber */       \
      NULL,                  /* PreviousVariable */      \
      NULL,                  /* NextVariable */          \
      0,                     /* ActiveReaders */         \
      0,                     /* OldValueBeingRead */     \
      0,                     /* TotalLogID */            \
      0},                    /* 5 min log ID */          \
     {NULL,                  /* Log flag parameter*/     \
    {.f64 = MinValue},       /* Min. limit*/             \
    {.f64 = MaxValue},       /* Max. limit*/             \
      Lists},                /* Selection list*/         \
      }
/* Macro defining Parameters with Min and Max limits defined */
#define VAR_ELEMENT_PARAMETER_U64(Name,AccessRead,AccessWrite,ScaleType,ScaleValue,Unit,Precision,InitValue,MinValue,MaxValue,Lists) \
	{                                  \
	{VAR_MAGIC_NUMBER,     /* Magic number */          \
	0,                     /* Hash value */            \
	NULL,                  /* Next variable in index */\
	Name,                  /* Name */                  \
	TYPE_U64,              /* Type */                  \
	AccessRead,            /* AccessRead */            \
	AccessWrite,           /* AccessWrite */           \
	ScaleType,             /* ScaleType */             \
	ScaleValue,            /* ScaleValue */            \
	Unit,                  /* Unit */                  \
	Precision,             /* Precision */             \
  {.u64 = InitValue},      /* Init value */            \
	0,                     /* Timestamp / Log flag */  \
	(scaletype_t)0,        /* DisplayScaleType */      \
	0,                     /* DisplayScaleValue */     \
	0,                     /* DisplayUnit */           \
	0,                     /* DisplayPrecision*/       \
	(enum update)PARAMETER,/* Update type */           \
	NULL,                  /* FirstSubscriber */       \
	NULL,                  /* PreviousVariable */      \
	NULL,                  /* NextVariable */          \
	0,                     /* ActiveReaders */         \
	0,                     /* OldValueBeingRead */     \
	0,                     /* TotalLogID */            \
	0},                    /* 5 min log ID */          \
   {NULL,                  /* Log flag parameter*/     \
  {.u64 = MinValue},       /* Min. limit*/             \
  {.u64 = MaxValue},       /* Max. limit*/             \
	Lists},                /* Selection list*/         \
	}

/* Macro defining Parameters with Min and Max limits defined */
#define VAR_ELEMENT_PARAMETER_S64(Name,AccessRead,AccessWrite,ScaleType,ScaleValue,Unit,Precision,InitValue,MinValue,MaxValue,Lists) \
	{                                  \
	{VAR_MAGIC_NUMBER,     /* Magic number */          \
	0,                     /* Hash value */            \
	NULL,                  /* Next variable in index */\
	Name,                  /* Name */                  \
	TYPE_S64,              /* Type */                  \
	AccessRead,            /* AccessRead */            \
	AccessWrite,           /* AccessWrite */           \
	ScaleType,             /* ScaleType */             \
	ScaleValue,            /* ScaleValue */            \
	Unit,                  /* Unit */                  \
	Precision,             /* Precision */             \
  {.s64 = InitValue},      /* Init value */            \
	0,                     /* Timestamp / Log flag */  \
	(scaletype_t)0,        /* DisplayScaleType */      \
	0,                     /* DisplayScaleValue */     \
	0,                     /* DisplayUnit */           \
	0,                     /* DisplayPrecision*/       \
	(enum update)PARAMETER,/* Update type */           \
	NULL,                  /* FirstSubscriber */       \
	NULL,                  /* PreviousVariable */      \
	NULL,                  /* NextVariable */          \
	0,                     /* ActiveReaders */         \
	0,                     /* OldValueBeingRead */     \
	0,                     /* TotalLogID */            \
	0},                    /* 5 min log ID */          \
   {NULL,                  /* Log flag parameter*/     \
  {.s64 = MinValue},       /* Min. limit*/             \
  {.s64 = MaxValue},       /* Max. limit*/             \
	Lists},                /* Selection list*/         \
	}

/* Macro defining Locals with Min and Max limits defined */
#define VAR_ELEMENT_LOCAL(Name,Type,AccessRead,AccessWrite,ScaleType,ScaleValue,Unit,Precision,InitValue,MinValue,MaxValue,Lists,LogFlag) \
   {                                  \
   {VAR_MAGIC_NUMBER, /* Magic number */          \
   0,                 /* Hash value */            \
   NULL,              /* Next variable in index */\
   Name,              /* Name */                  \
   Type,              /* Type */                  \
   AccessRead,        /* AccessRead */            \
   AccessWrite,       /* AccessWrite */           \
   ScaleType,         /* ScaleType */             \
   ScaleValue,        /* ScaleValue */            \
   Unit,              /* Unit */                  \
   Precision,         /* Precision */             \
 {(char *) InitValue},/* Init value */            \
   LogFlag,           /* Timestamp / Log flag */  \
   (scaletype_t)0,    /* DisplayScaleType */      \
   (scalevalue_t)0,   /* DisplayScaleValue */     \
   (unit_t)0,         /* DisplayUnit */           \
   0,                 /* DisplayPrecision*/       \
   (enum update)LOCAL,/* Update type */           \
   NULL,              /* FirstSubscriber */       \
   NULL,              /* PreviousVariable */      \
   NULL,              /* NextVariable */          \
   0,                 /* ActiveReaders */         \
   0,                 /* OldValueBeingRead */     \
   0,                 /* TotalLogID */            \
   0},                /* 5 min log ID */          \
   {NULL,             /* Log flag parameter*/     \
  {(char *)MinValue}, /* Min. limit*/             \
  {(char *)MaxValue}, /* Max. limit*/             \
   Lists},            /* Selection list*/         \
   }
/* Macro defining Locals with Min and Max limits defined */
#define VAR_ELEMENT_LOCAL_F32(Name,AccessRead,AccessWrite,Unit,Precision,InitValue,MinValue,MaxValue,Lists,LogFlag) \
      {                                  \
      {VAR_MAGIC_NUMBER, /* Magic number */          \
      0,                 /* Hash value */            \
      NULL,              /* Next variable in index */\
      Name,              /* Name */                  \
      TYPE_F32,          /* Type */                  \
      AccessRead,        /* AccessRead */            \
      AccessWrite,       /* AccessWrite */           \
      0,                 /* ScaleType */             \
      0,                 /* ScaleValue */            \
      Unit,              /* Unit */                  \
      Precision,         /* Precision */             \
     {.f32 = InitValue}, /* Init value */            \
      LogFlag,           /* Timestamp / Log flag */  \
      (scaletype_t)0,    /* DisplayScaleType */      \
      (scalevalue_t)0,   /* DisplayScaleValue */     \
      (unit_t)0,         /* DisplayUnit */           \
      0,                 /* DisplayPrecision*/       \
      (enum update)LOCAL,/* Update type */           \
      NULL,              /* FirstSubscriber */       \
      NULL,              /* PreviousVariable */      \
      NULL,              /* NextVariable */          \
      0,                 /* ActiveReaders */         \
      0,                 /* OldValueBeingRead */     \
      0,                 /* TotalLogID */            \
      0},                /* 5 min log ID */          \
      {NULL,             /* Log flag parameter*/     \
     {.f32 = MinValue},  /* Min. limit*/             \
     {.f32 = MaxValue},  /* Max. limit*/             \
      Lists},            /* Selection list*/         \
      }
/* Macro defining Locals with Min and Max limits defined */
#define VAR_ELEMENT_LOCAL_F64(Name,AccessRead,AccessWrite,Unit,Precision,InitValue,MinValue,MaxValue,Lists,LogFlag) \
	 {                                  \
	 {VAR_MAGIC_NUMBER, /* Magic number */          \
	 0,                 /* Hash value */            \
	 NULL,              /* Next variable in index */\
	 Name,              /* Name */                  \
	 TYPE_F64,          /* Type */                  \
	 AccessRead,        /* AccessRead */            \
	 AccessWrite,       /* AccessWrite */           \
	 0,                 /* ScaleType */             \
	 0,                 /* ScaleValue */            \
	 Unit,              /* Unit */                  \
	 Precision,         /* Precision */             \
	{.f64 = InitValue}, /* Init value */            \
	 LogFlag,           /* Timestamp / Log flag */  \
	 (scaletype_t)0,    /* DisplayScaleType */      \
	 (scalevalue_t)0,   /* DisplayScaleValue */     \
	 (unit_t)0,         /* DisplayUnit */           \
	 0,                 /* DisplayPrecision*/       \
	 (enum update)LOCAL,/* Update type */           \
	 NULL,              /* FirstSubscriber */       \
	 NULL,              /* PreviousVariable */      \
	 NULL,              /* NextVariable */          \
	 0,                 /* ActiveReaders */         \
	 0,                 /* OldValueBeingRead */     \
	 0,                 /* TotalLogID */            \
	 0},                /* 5 min log ID */          \
	 {NULL,             /* Log flag parameter*/     \
	{.f64 = MinValue},  /* Min. limit*/             \
	{.f64 = MaxValue},  /* Max. limit*/             \
	 Lists},            /* Selection list*/         \
	 }
/* Macro defining Locals with Min and Max limits defined */
#define VAR_ELEMENT_LOCAL_U64(Name,AccessRead,AccessWrite,ScaleType,ScaleValue,Unit,Precision,InitValue,MinValue,MaxValue,Lists,LogFlag) \
	 {                                  \
	 {VAR_MAGIC_NUMBER, /* Magic number */          \
	 0,                 /* Hash value */            \
	 NULL,              /* Next variable in index */\
	 Name,              /* Name */                  \
	 TYPE_U64,          /* Type */                  \
	 AccessRead,        /* AccessRead */            \
	 AccessWrite,       /* AccessWrite */           \
	 ScaleType,         /* ScaleType */             \
	 ScaleValue,        /* ScaleValue */            \
	 Unit,              /* Unit */                  \
	 Precision,         /* Precision */             \
	{.u64 = InitValue}, /* Init value */            \
	 LogFlag,           /* Timestamp / Log flag */  \
	 (scaletype_t)0,    /* DisplayScaleType */      \
	 (scalevalue_t)0,   /* DisplayScaleValue */     \
	 (unit_t)0,         /* DisplayUnit */           \
	 0,                 /* DisplayPrecision*/       \
	 (enum update)LOCAL,/* Update type */           \
	 NULL,              /* FirstSubscriber */       \
	 NULL,              /* PreviousVariable */      \
	 NULL,              /* NextVariable */          \
	 0,                 /* ActiveReaders */         \
	 0,                 /* OldValueBeingRead */     \
	 0,                 /* TotalLogID */            \
	 0},                /* 5 min log ID */          \
	 {NULL,             /* Log flag parameter*/     \
	{.u64 = MinValue},  /* Min. limit*/             \
	{.u64 = MaxValue},  /* Max. limit*/             \
	 Lists},            /* Selection list*/         \
	 }
/* Macro defining Locals with Min and Max limits defined */
#define VAR_ELEMENT_LOCAL_S64(Name,AccessRead,AccessWrite,ScaleType,ScaleValue,Unit,Precision,InitValue,MinValue,MaxValue,Lists,LogFlag) \
	 {                                  \
	 {VAR_MAGIC_NUMBER, /* Magic number */          \
	 0,                 /* Hash value */            \
	 NULL,              /* Next variable in index */\
	 Name,              /* Name */                  \
	 TYPE_S64,          /* Type */                  \
	 AccessRead,        /* AccessRead */            \
	 AccessWrite,       /* AccessWrite */           \
	 ScaleType,         /* ScaleType */             \
	 ScaleValue,        /* ScaleValue */            \
	 Unit,              /* Unit */                  \
	 Precision,         /* Precision */             \
	{.s64 = InitValue}, /* Init value */            \
	 LogFlag,           /* Timestamp / Log flag */  \
	 (scaletype_t)0,    /* DisplayScaleType */      \
	 (scalevalue_t)0,   /* DisplayScaleValue */     \
	 (unit_t)0,         /* DisplayUnit */           \
	 0,                 /* DisplayPrecision*/       \
	 (enum update)LOCAL,/* Update type */           \
	 NULL,              /* FirstSubscriber */       \
	 NULL,              /* PreviousVariable */      \
	 NULL,              /* NextVariable */          \
	 0,                 /* ActiveReaders */         \
	 0,                 /* OldValueBeingRead */     \
	 0,                 /* TotalLogID */            \
	 0},                /* 5 min log ID */          \
	 {NULL,             /* Log flag parameter*/     \
	{.s64 = MinValue},  /* Min. limit*/             \
	{.s64 = MaxValue},  /* Max. limit*/             \
	 Lists},            /* Selection list*/         \
	 }

#define VAR_ELEMENT_OUTPUT_PARAMETER(Name,Type,AccessRead,AccessWrite,ScaleType,ScaleValue,Unit,Precision,InitValue,MinValue,MaxValue,Lists) \
   {                                  \
   {VAR_MAGIC_NUMBER,     /* Magic number */          \
   0,                     /* Hash value */            \
   NULL,                  /* Next variable in index */\
   Name,                  /* Name */                  \
   Type,                  /* Type */                  \
   AccessRead,            /* AccessRead */            \
   AccessWrite,           /* AccessWrite */           \
   ScaleType,             /* ScaleType */             \
   ScaleValue,            /* ScaleValue */            \
   Unit,                  /* Unit */                  \
   Precision,             /* Precision */             \
 {(char *) InitValue},    /* Init value */            \
   0,                     /* Timestamp / Log flag */  \
   (scaletype_t)0,        /* DisplayScaleType */      \
   0,                     /* DisplayScaleValue */     \
   0,                     /* DisplayUnit */           \
   0,                     /* DisplayPrecision*/       \
   (enum update)OUTPUT_PARAMETER,/* Update type */    \
   NULL,                  /* FirstSubscriber */       \
   NULL,                  /* PreviousVariable */      \
   NULL,                  /* NextVariable */          \
   0,                     /* ActiveReaders */         \
   0,                     /* OldValueBeingRead */     \
   0,                     /* TotalLogID */            \
   0},                    /* 5 min log ID */          \
   {0},                   /* wpline info */           \
  {NULL,                  /* Log flag parameter*/     \
 {(char *)MinValue},      /* Min. limit*/             \
 {(char *)MaxValue},      /* Max. limit*/             \
   Lists},                /* Selection list*/         \
}	 
	 
/* Macro defining Backups with Min and Max limits defined */
#define VAR_ELEMENT_BACKUP(Name,Type,AccessRead,AccessWrite,ScaleType,ScaleValue,Unit,Precision,InitValue,MinValue,MaxValue,Lists,LogFlag) \
   {                                  \
   {VAR_MAGIC_NUMBER,  /* Magic number */          \
   0,                  /* Hash value */            \
   NULL,               /* Next variable in index */\
   Name,               /* Name */                  \
   Type,               /* Type */                  \
   AccessRead,         /* AccessRead */            \
   AccessWrite,        /* AccessWrite */           \
   ScaleType,          /* ScaleType */             \
   ScaleValue,         /* ScaleValue */            \
   Unit,               /* Unit */                  \
   Precision,          /* Precision */             \
  {(char *) InitValue},/* Init value */            \
   LogFlag,            /* Timestamp / Log flag */  \
   (scaletype_t)0,     /* DisplayScaleType */      \
   0,                  /* DisplayScaleValue */     \
   0,                  /* DisplayUnit */           \
   0,                  /* DisplayPrecision*/       \
   (enum update)BACKUP,/* Update type */           \
   NULL,               /* FirstSubscriber */       \
   NULL,               /* PreviousVariable */      \
   NULL,               /* NextVariable */          \
   0,                  /* ActiveReaders */         \
   0,                  /* OldValueBeingRead */     \
   0,                  /* TotalLogID */            \
   0},                 /* 5 min log ID */          \
   {NULL,              /* Log flag parameter*/     \
   NULL,               /* Fileid */                \
   0,                  /* Change flag */           \
  {(char *)MinValue},  /* Min. limit*/             \
  {(char *)MaxValue},  /* Max. limit*/             \
   Lists},             /* Selection list*/         \
   }

/* Macro defining Backups with Min and Max limits defined */
#define VAR_ELEMENT_BACKUP_F32(Name,AccessRead,AccessWrite,Unit,Precision,InitValue,MinValue,MaxValue,Lists,LogFlag) \
      {                                  \
      {VAR_MAGIC_NUMBER,  /* Magic number */          \
      0,                  /* Hash value */            \
      NULL,               /* Next variable in index */\
      Name,               /* Name */                  \
      TYPE_F32,           /* Type */                  \
      AccessRead,         /* AccessRead */            \
      AccessWrite,        /* AccessWrite */           \
      0,                  /* ScaleType */             \
      0,                  /* ScaleValue */            \
      Unit,               /* Unit */                  \
      Precision,          /* Precision */             \
     {.f32 = InitValue},  /* Init value */            \
      LogFlag,            /* Timestamp / Log flag */  \
      (scaletype_t)0,     /* DisplayScaleType */      \
      0,                  /* DisplayScaleValue */     \
      0,                  /* DisplayUnit */           \
      0,                  /* DisplayPrecision*/       \
      (enum update)BACKUP,/* Update type */           \
      NULL,               /* FirstSubscriber */       \
      NULL,               /* PreviousVariable */      \
      NULL,               /* NextVariable */          \
      0,                  /* ActiveReaders */         \
      0,                  /* OldValueBeingRead */     \
      0,                  /* TotalLogID */            \
      0},                 /* 5 min log ID */          \
      {NULL,              /* Log flag parameter*/     \
      NULL,               /* Fileid */                \
      0,                  /* Change flag */           \
     {.f32 = MinValue},   /* Min. limit*/             \
     {.f32 = MaxValue},   /* Max. limit*/             \
      Lists},             /* Selection list*/         \
      }

/* Macro defining Backups with Min and Max limits defined */
#define VAR_ELEMENT_BACKUP_F64(Name,AccessRead,AccessWrite,Unit,Precision,InitValue,MinValue,MaxValue,Lists,LogFlag) \
	{                                  \
	{VAR_MAGIC_NUMBER,  /* Magic number */          \
	0,                  /* Hash value */            \
	NULL,               /* Next variable in index */\
	Name,               /* Name */                  \
	TYPE_F64,           /* Type */                  \
	AccessRead,         /* AccessRead */            \
	AccessWrite,        /* AccessWrite */           \
	0,                  /* ScaleType */             \
	0,                  /* ScaleValue */            \
	Unit,               /* Unit */                  \
	Precision,          /* Precision */             \
   {.f64 = InitValue},  /* Init value */            \
	LogFlag,            /* Timestamp / Log flag */  \
	(scaletype_t)0,     /* DisplayScaleType */      \
	0,                  /* DisplayScaleValue */     \
	0,                  /* DisplayUnit */           \
	0,                  /* DisplayPrecision*/       \
	(enum update)BACKUP,/* Update type */           \
	NULL,               /* FirstSubscriber */       \
	NULL,               /* PreviousVariable */      \
	NULL,               /* NextVariable */          \
	0,                  /* ActiveReaders */         \
	0,                  /* OldValueBeingRead */     \
	0,                  /* TotalLogID */            \
	0},                 /* 5 min log ID */          \
	{NULL,              /* Log flag parameter*/     \
	NULL,               /* Fileid */                \
	0,                  /* Change flag */           \
   {.f64 = MinValue},   /* Min. limit*/             \
   {.f64 = MaxValue},   /* Max. limit*/             \
	Lists},             /* Selection list*/         \
	}
/* Macro defining Backups with Min and Max limits defined */
#define VAR_ELEMENT_BACKUP_U64(Name,AccessRead,AccessWrite,ScaleType,ScaleValue,Unit,Precision,InitValue,MinValue,MaxValue,Lists,LogFlag) \
	{                                  \
	{VAR_MAGIC_NUMBER,  /* Magic number */          \
	0,                  /* Hash value */            \
	NULL,               /* Next variable in index */\
	Name,               /* Name */                  \
	TYPE_U64,           /* Type */                  \
	AccessRead,         /* AccessRead */            \
	AccessWrite,        /* AccessWrite */           \
	ScaleType,          /* ScaleType */             \
	ScaleValue,         /* ScaleValue */            \
	Unit,               /* Unit */                  \
	Precision,          /* Precision */             \
   {.u64 = InitValue},  /* Init value */            \
	LogFlag,            /* Timestamp / Log flag */  \
	(scaletype_t)0,     /* DisplayScaleType */      \
	0,                  /* DisplayScaleValue */     \
	0,                  /* DisplayUnit */           \
	0,                  /* DisplayPrecision*/       \
	(enum update)BACKUP,/* Update type */           \
	NULL,               /* FirstSubscriber */       \
	NULL,               /* PreviousVariable */      \
	NULL,               /* NextVariable */          \
	0,                  /* ActiveReaders */         \
	0,                  /* OldValueBeingRead */     \
	0,                  /* TotalLogID */            \
	0},                 /* 5 min log ID */          \
	{NULL,              /* Log flag parameter*/     \
	NULL,               /* Fileid */                \
	0,                  /* Change flag */           \
   {.u64 = MinValue},   /* Min. limit*/             \
   {.u64 = MaxValue},   /* Max. limit*/             \
	Lists},             /* Selection list*/         \
	}

/* Macro defining Backups with Min and Max limits defined */
#define VAR_ELEMENT_BACKUP_S64(Name,AccessRead,AccessWrite,ScaleType,ScaleValue,Unit,Precision,InitValue,MinValue,MaxValue,Lists,LogFlag) \
	{                                  \
	{VAR_MAGIC_NUMBER,  /* Magic number */          \
	0,                  /* Hash value */            \
	NULL,               /* Next variable in index */\
	Name,               /* Name */                  \
	TYPE_S64,           /* Type */                  \
	AccessRead,         /* AccessRead */            \
	AccessWrite,        /* AccessWrite */           \
	ScaleType,          /* ScaleType */             \
	ScaleValue,         /* ScaleValue */            \
	Unit,               /* Unit */                  \
	Precision,          /* Precision */             \
   {.s64 = InitValue},  /* Init value */            \
	LogFlag,            /* Timestamp / Log flag */  \
	(scaletype_t)0,     /* DisplayScaleType */      \
	0,                  /* DisplayScaleValue */     \
	0,                  /* DisplayUnit */           \
	0,                  /* DisplayPrecision*/       \
	(enum update)BACKUP,/* Update type */           \
	NULL,               /* FirstSubscriber */       \
	NULL,               /* PreviousVariable */      \
	NULL,               /* NextVariable */          \
	0,                  /* ActiveReaders */         \
	0,                  /* OldValueBeingRead */     \
	0,                  /* TotalLogID */            \
	0},                 /* 5 min log ID */          \
	{NULL,              /* Log flag parameter*/     \
	NULL,               /* Fileid */                \
	0,                  /* Change flag */           \
   {.s64 = MinValue},   /* Min. limit*/             \
   {.s64 = MaxValue},   /* Max. limit*/             \
	Lists},             /* Selection list*/         \
	}

/* Macro defining Systems with Min and Max limits defined */
#define VAR_ELEMENT_SYSTEM_RO(Name,Type,AccessRead,AccessWrite,ScaleType,ScaleValue,Unit,Precision) \
   {                                                  \
  {VAR_MAGIC_NUMBER,     /* Magic number */          \
   0,                     /* Hash value */            \
   NULL,                  /* Next variable in index */\
   Name,                  /* Name */                  \
   Type,                  /* Type */                  \
   AccessRead,            /* AccessRead */            \
   AccessWrite,           /* AccessWrite */           \
   ScaleType,             /* ScaleType */             \
   ScaleValue,            /* ScaleValue */            \
   Unit,                  /* Unit */                  \
   Precision,             /* Precision */             \
 {(char *) NULL},         /* Init value */            \
   0,                     /* Timestamp / Log flag */  \
   (scaletype_t)0,        /* DisplayScaleType */      \
   (scalevalue_t)0,       /* DisplayScaleValue */     \
   (unit_t)0,             /* DisplayUnit */           \
   0,                     /* DisplayPrecision*/       \
   (enum update)SYSTEM_RO,/* Update type */           \
   NULL,                  /* FirstSubscriber */       \
   NULL,                  /* PreviousVariable */      \
   NULL,                  /* NextVariable */          \
   0,                     /* ActiveReaders */         \
   0,                     /* OldValueBeingRead */     \
   0,                     /* TotalLogID */            \
   0},                    /* 5 min log ID */          \
  {0                      /* PROMReference*/           \
   }}

/* Macro defining Systems with Min and Max limits defined */
#define VAR_ELEMENT_SYSTEM(Name,Type,AccessRead,AccessWrite,ScaleType,ScaleValue,Unit,Precision,InitValue,MinValue,MaxValue,Lists,LogFlag) \
   {                                  \
   {VAR_MAGIC_NUMBER,  /* Magic number */          \
   0,                  /* Hash value */            \
   NULL,               /* Next variable in index */\
   Name,               /* Name */                  \
   Type,               /* Type */                  \
   AccessRead,         /* AccessRead */            \
   AccessWrite,        /* AccessWrite */           \
   ScaleType,          /* ScaleType */             \
   ScaleValue,         /* ScaleValue */            \
   Unit,               /* Unit */                  \
   Precision,          /* Precision */             \
 {(char *) InitValue}, /* Init Value */            \
   LogFlag,            /* Timestamp / Log flag */  \
   (scaletype_t)0,     /* DisplayScaleType */      \
   (scalevalue_t)0,    /* DisplayScaleValue */     \
   (unit_t)0,          /* DisplayUnit */           \
   0,                  /* DisplayPrecision*/       \
   (enum update)SYSTEM,/* Update type */           \
   NULL,               /* FirstSubscriber */       \
   NULL,               /* PreviousVariable */      \
   NULL,               /* NextVariable */          \
   0,                  /* ActiveReaders */         \
   0,                  /* OldValueBeingRead */     \
   0,                  /* TotalLogID */            \
   0},                 /* 5 min log ID */          \
   {NULL,              /* Log flag parameter*/     \
   0,                  /* PROMReference*/          \
  {(char *)MinValue},  /* Min. limit*/             \
  {(char *)MaxValue},  /* Max. limit*/             \
   Lists,              /* Selection list*/         \
  {(char *)NULL}},      /* Default       */         \
   {0},                                             \
   {0}                                              \
   }

#define VAR_ELEMENT_TIMER(Name,Type,AccessRead,AccessWrite,ScaleType,ScaleValue,Unit,Precision,InitValue) \
   {                                     \
   {VAR_MAGIC_NUMBER,   /* Magic number */          \
   0,                  /* Hash value */            \
   NULL,               /* Next variable in index */\
   Name,               /* Name */                  \
   Type,               /* Type */                  \
   AccessRead,         /* AccessRead */            \
   AccessWrite,        /* AccessWrite */           \
   ScaleType,          /* ScaleType */             \
   ScaleValue,         /* ScaleValue */            \
   Unit,               /* Unit */                  \
   Precision,          /* Precision */             \
 {(char *) InitValue}, /* Value */                 \
   0,                  /* Timestamp / Log flag */  \
   (scaletype_t)0,     /* DisplayScaleType */      \
   (scalevalue_t)0,    /* DisplayScaleValue */     \
   (unit_t)0,          /* DisplayUnit */           \
   0,                  /* DisplayPrecision*/       \
   (enum update)TIMER, /* Update type */           \
   NULL,               /* FirstSubscriber */       \
   NULL,               /* PreviousVariable */      \
   NULL,               /* NextVariable */          \
   0,                  /* ActiveReaders */         \
   0,                  /* OldValueBeingRead */     \
   0,                  /* TotalLogID */            \
   0},                 /* 5 min log ID */          \
   }

#define VAR_ELEMENT_ENERGY_SUM(Name, AccessRead, AccessWrite, ProducedActiveVariable, ConsumedActiveVariable, ProducedReactiveVariable, ConsumedReactiveVariable, EnergySummation) \
   {                                                                    \
      {                                                                 \
         VAR_MAGIC_NUMBER,                /* Magic number */            \
         0,                               /* Hash value */              \
         NULL,                            /* Next variable in index */  \
         Name,                            /* Name */                    \
         TYPE_ESUM,                       /* Type */                    \
         AccessRead,                      /* AccessRead */              \
         AccessWrite,                     /* AccessWrite */             \
         (scaletype_t)SCALE_NONE,         /* ScaleType */               \
         (scalevalue_t)0,                 /* ScaleValue */              \
         (unit_t)UNIT_NONE,               /* Unit */                    \
         0,                               /* Precision */               \
         {(char *)&EnergySummation},      /* Value */                   \
         0,                               /* Timestamp */               \
         (scaletype_t)0,                  /* DisplayScaleType */        \
         (scalevalue_t)0,                 /* DisplayScaleValue */       \
         (unit_t)0,                       /* DisplayUnit */             \
         0,                               /* DisplayPrecision*/         \
         (enum update)SUMMATION,          /* Update */                  \
         NULL,                            /* FirstSubscriber */         \
         NULL,                            /* PreviousVariable */        \
         NULL,                            /* NextVariable */            \
         0,                               /* ActiveReaders */           \
         0,                               /* OldValueBeingRead */       \
         0,                               /* TotalLogID */              \
         0                                /* 5 min log ID */            \
      },                                                                \
      {                                                                 \
         NULL,                            /* FileID */                  \
         0,                               /* ChangeFlag */              \
         (char *)ProducedActiveVariable,  /* FirstVariable */           \
         (char *)ConsumedActiveVariable,  /* SecondVariable */          \
         (char *)ProducedReactiveVariable,/* ThirdVariable */           \
         (char *)ConsumedReactiveVariable,/* FourthVariable */          \
      }                                                                 \
   }

#define VAR_ELEMENT_SERVICE_SUM(Name, AccessRead, AccessWrite, StateVariable, ServiceSummation) \
   {                                                                 \
      {                                                              \
         VAR_MAGIC_NUMBER,             /* Magic number */            \
         0,                            /* Hash value */              \
         NULL,                         /* Next variable in index */  \
         Name,                         /* Name */                    \
         TYPE_SSUM,                    /* Type */                    \
         AccessRead,                   /* AccessRead */              \
         AccessWrite,                  /* AccessWrite */             \
         (scaletype_t)SCALE_NONE,      /* ScaleType */               \
         (scalevalue_t)0,              /* ScaleValue */              \
         (unit_t)UNIT_NONE,            /* Unit */                    \
         0,                            /* Precision */               \
         {(char *)&ServiceSummation},  /* Value */                   \
         0,                            /* Timestamp */               \
         (scaletype_t)0,               /* DisplayScaleType */        \
         (scalevalue_t)0,              /* DisplayScaleValue */       \
         (unit_t)0,                    /* DisplayUnit */             \
         0,                            /* DisplayPrecision*/         \
         (enum update)SUMMATION,       /* Update */                  \
         NULL,                         /* FirstSubscriber */         \
         NULL,                         /* PreviousVariable */        \
         NULL,                         /* NextVariable */            \
         0,                            /* ActiveReaders */           \
         0,                            /* OldValueBeingRead */       \
         0,                            /* TotalLogID */              \
         0,                            /* 5 min log ID */            \
      },                                                             \
      {                                                              \
         NULL,                         /* FileID */                  \
         0,                            /* ChangeFlag */              \
         (char*)StateVariable,         /* FirstVariable */           \
         NULL,                         /* SecondVariable */          \
         NULL,                         /* ThirdVariable */           \
         NULL,                         /* FourthVariable */          \
      }                                                              \
   }

#define VAR_ELEMENT_SIMPLE_SUM(Name,AccessRead,AccessWrite,UpdateVariable,SimpleSummation) \
   {                                  \
   	  {                                \
		VAR_MAGIC_NUMBER,        /* Magic number */          \
   		0,                       /* Hash value */            \
   		NULL,                    /* Next variable in index */\
   		Name,                    /* Name */                  \
   		TYPE_SUM,                /* Type */                  \
   		AccessRead,              /* AccessRead */            \
   		AccessWrite,             /* AccessWrite */           \
   		(scaletype_t)SCALE_NONE, /* ScaleType */             \
   		(scalevalue_t)0,         /* ScaleValue */            \
   		(unit_t)UNIT_NONE,       /* Unit */                  \
   		0,                       /* Precision */             \
   		{(char *)&SimpleSummation},/* Value */                 \
   		0,                       /* Timestamp */             \
   		(scaletype_t)0,          /* DisplayScaleType */      \
   		(scalevalue_t)0,         /* DisplayScaleValue */     \
   		(unit_t)0,               /* DisplayUnit */           \
   		0,                       /* DisplayPrecision*/       \
   		(enum update)SUMMATION,  /* Update */                \
   		NULL,                    /* FirstSubscriber */       \
   		NULL,                    /* PreviousVariable */      \
   		NULL,                    /* NextVariable */          \
   		0,                       /* ActiveReaders */         \
   		0,                       /* OldValueBeingRead */     \
   		0,                       /* TotalLogID */            \
   		0,                       /* 5 min log ID */          \
	  },                                                     \
	  {                                                      \
   		NULL,                    /* FileID */                \
   		0,                       /* ChangeFlag */            \
   		(char *)UpdateVariable,  /* FirstVariable */         \
   		NULL,                    /* SecondVariable */        \
   		NULL,                    /* ThirdVariable */         \
   		NULL,                    /* FourthVariable */        \
	  }                                                      \
   }

#define VAR_ELEMENT_STATISTIC_SUM(Name,AccessRead,AccessWrite,UpdateVariable, StateVariable, UpdateInterval, StaticSummation) \
   {                                  \
        {                                \
      VAR_MAGIC_NUMBER,        /* Magic number */          \
         0,                       /* Hash value */            \
         NULL,                    /* Next variable in index */\
         Name,                    /* Name */                  \
         TYPE_STATSUM,                /* Type */                  \
         AccessRead,              /* AccessRead */            \
         AccessWrite,             /* AccessWrite */           \
         (scaletype_t)SCALE_NONE, /* ScaleType */             \
         (scalevalue_t)0,         /* ScaleValue */            \
         (unit_t)UNIT_NONE,       /* Unit */                  \
         0,                       /* Precision */             \
         {(char *)&StaticSummation},/* Value */                 \
         0,                       /* Timestamp */             \
         (scaletype_t)0,          /* DisplayScaleType */      \
         (scalevalue_t)0,         /* DisplayScaleValue */     \
         (unit_t)0,               /* DisplayUnit */           \
         0,                       /* DisplayPrecision*/       \
         (enum update)SUMMATION,  /* Update */                \
         NULL,                    /* FirstSubscriber */       \
         NULL,                    /* PreviousVariable */      \
         NULL,                    /* NextVariable */          \
         0,                       /* ActiveReaders */         \
         0,                       /* OldValueBeingRead */     \
         0,                       /* TotalLogID */            \
         0,                       /* 5 min log ID */          \
     },                                                     \
     {                                                      \
         NULL,                    /* FileID */                \
         0,                       /* ChangeFlag */            \
         (char *)UpdateVariable,  /* FirstVariable */         \
         (char *)StateVariable,   /* SecondVariable */        \
         (char *)UpdateInterval,  /* ThirdVariable */         \
         NULL,                    /* FourthVariable */        \
     }                                                      \
   }

#define VAR_ELEMENT_AVAILABILITY(Name,AccessRead,AccessWrite,av_pointer) \
   {                                  \
   {VAR_MAGIC_NUMBER,       /* Magic number */          \
   0,                       /* Hash value */            \
   NULL,                    /* Next variable in index */\
   Name,                    /* Name */\
   TYPE_AVAIL,              /* Type */\
   AccessRead,              /* AccessRead */\
   AccessWrite,             /* AccessWrite */\
   (scaletype_t)SCALE_NONE, /* ScaleType */\
   (scalevalue_t)1,         /* ScaleValue */\
   (unit_t)UNIT_NONE,       /* Unit */\
   0,                       /* Precision */\
 {(char *)&av_pointer},     /* Value */\
   0,                       /* Timestamp */\
   (scaletype_t)SCALE_NONE, /* DisplayScaleType */\
   (scalevalue_t)1,         /* DisplayScaleValue */\
   (unit_t)UNIT_NONE,       /* DisplayUnit */\
   0,                       /* DisplayPrecision*/\
   (enum update)AVAILABILITY,/* Update */\
   NULL,                    /* FirstSubscriber */\
   NULL,                    /* PreviousVariable */\
   NULL,                    /* NextVariable */\
   0,                       /* ActiveReaders */\
   0,                       /* OldValueBeingRead */\
   0},                       /* TotalLogID */\
   {NULL,                    /* FileID */\
   0},                       /* ChangeFlag */\
   }
#define VAR_ELEMENT_ALIAS(Name,Alias) \
   {                                  \
   ALIAS_MAGIC_NUMBER, /* Magic number */          \
   0,                  /* Hash value */            \
   NULL,               /* Next variable in index */\
   Alias,              /* Alias name*/             \
   Name,               /* Name */                  \
   NULL,               /* Parent variable */       \
   }


typedef enum { WLO_TYPE, WLO_MIN, WLO_MAX, WLO_LIST } WHICH_LIST_OFFSET;

#endif
