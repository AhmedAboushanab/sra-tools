/*===========================================================================
*
*                            PUBLIC DOMAIN NOTICE
*               National Center for Biotechnology Information
*
*  This software/database is a "United States Government Work" under the
*  terms of the United States Copyright Act.  It was written as part of
*  the author's official duties as a United States Government employee and
*  thus cannot be copyrighted.  This software/database is freely available
*  to the public for use. The National Library of Medicine and the U.S.
*  Government have not placed any restriction on its use or reproduction.
*
*  Although all reasonable efforts have been taken to ensure the accuracy
*  and reliability of the software and data, the NLM and the U.S.
*  Government do not and cannot warrant the performance or results that
*  may be obtained by using this software or data. The NLM and the U.S.
*  Government disclaim all warranties, express or implied, including
*  warranties of performance, merchantability or fitness for any particular
*  purpose.
*
*  Please cite the author in any work or product based on this material.
*
* ===========================================================================
*
*/

#ifndef _delite_s_h_
#define _delite_s_h_

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

/*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*
 *  That file represents SCHEMA parsing and editing
 *
 *  Das JOJOBA!
 *
 *_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*/
struct karChiveScm;
struct KMetadata;


/*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*
 *  UnOficial schema resolvin unit
 *
 *  By default schema will be resolved with using 'DELITE' section
 *  from Konfig.
 *
 *  User may define his own Konfig, in that case he could load it 
 *  with karChiveScmSetStandardResolver () method.
 *
 *  If user want to use his own resolving mechanism, he could set an 
 *  instance of resolver with ksrChiveScmSetResolver method
 *
 *_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*/
struct karChiveResolver {
    void * _data;

        /*  Note, returned SchemaPath and SchemaName will be
         *  freed by caller ... so, please do not return any
         *  valuables
         */
    rc_t ( CC * _resolve ) ( 
                            struct karChiveResolver * Resolver,
                            const char * Name,
                            char ** SchemaPath,
                            char ** SchemaName
                            );

        /*  if dat will be NULL, resolver will be 'free()'
         */
    rc_t ( CC * _dispose ) ( struct karChiveResolver * Resolver );
};

    /*  Once resolver is set, any attempt to set another will be
     *  rejected, lol
     */
rc_t CC karChiveScmSetStandardResolver (
                            struct karChiveScm * self,
                            const char * KfgPath
                            );

    /*  Once resolver is set, any attempt to set another will be
     *  rejected, lol
     */
rc_t CC ksrChiveScmSetResolver ( 
                            struct karChiveScm * self,
                            struct karChiveResolver * Rsl
                            );

/*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*
 *  Oficial schema processing unit
 *
 *_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*/
rc_t CC karChiveScmMake ( struct karChiveScm ** Scm );
rc_t CC karChiveScmDispose ( struct karChiveScm * self );

    /*  NOTE: 'schema_name' parameter could be null, in that
     *      case original name will be used
     *      NewSchemaName will not be disposed, so it is caller prblem
     */
rc_t CC karChiveScmTransform (
                            struct karChiveScm * self,
                            struct KMetadata * Meta
                            );


#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* _delite_s_h_ */