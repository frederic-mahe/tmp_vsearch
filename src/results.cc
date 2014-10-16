/*
  Copyright (C) 2014 Torbjorn Rognes

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU Affero General Public License as
  published by the Free Software Foundation, either version 3 of the
  License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Affero General Public License for more details.

  You should have received a copy of the GNU Affero General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

  Contact: Torbjorn Rognes <torognes@ifi.uio.no>,
  Department of Informatics, University of Oslo,
  PO Box 1080 Blindern, NO-0316 Oslo, Norway
*/

#include "vsearch.h"

void results_show_fastapairs_one(FILE * fp,
                                 struct hit * hp,
                                 char * query_head,
                                 char * qsequence,
                                 long qseqlen,
                                 char * rc)
{
  /* http://www.drive5.com/usearch/manual/fastapairs.html */
  
  if (hp)
    {
      char * qrow = align_getrow(hp->strand ? rc : qsequence,
                                 hp->nwalignment,
                                 hp->nwalignmentlength,
                                 0);
      fprint_fasta_hdr_only(fp, query_head);
      fprint_fasta_seq_only(fp, qrow + hp->trim_q_left + hp->trim_t_left,
                            hp->internal_alignmentlength, 0);
      free(qrow);
      
      char * trow = align_getrow(db_getsequence(hp->target),
                                 hp->nwalignment,
                                 hp->nwalignmentlength,
                                 1);
      fprint_fasta_hdr_only(fp, db_getheader(hp->target));
      fprint_fasta_seq_only(fp, trow + hp->trim_q_left + hp->trim_t_left,
                            hp->internal_alignmentlength, 0);
      free(trow);
      
      fprintf(fp, "\n");
    }
}


void results_show_blast6out_one(FILE * fp,
                                struct hit * hp,
                                char * query_head,
                                char * qsequence, 
                                long qseqlen,
                                char * rc)
{

  /* 
     http://www.drive5.com/usearch/manual/blast6out.html
  
     query label
     target label
     percent identity
     alignment length
     number of mismatches
     number of gap opens
     1-based position of start in query
     1-based position of end in query
     1-based position of start in target
     1-based position of end in target
     E-value
     bit score
  */
  
  if (hp)
    {
      long qstart, qend;
      
      if (hp->strand)
        {
          /* minus strand */
          qstart = qseqlen;
          qend = 1;
        }
      else
        {
          /* plus strand */
          qstart = 1;
          qend = qseqlen;
        }
      
      fprintf(fp,
              "%s\t%s\t%.1f\t%ld\t%ld\t%ld\t%ld\t%ld\t%ld\t%ld\t*\t*\n",
              query_head,
              db_getheader(hp->target),
              hp->internal_id,
              hp->internal_alignmentlength,
              hp->mismatches,
              hp->internal_gaps,
              qstart,
              qend,
              1L,
              db_getsequencelen(hp->target));
    }
  else
    {
        fprintf(fp, "%s\t*\t0\t0\t0\t0\t0\t0\t0\t0\t0\t*\t0\n", query_head);
    }
}

void results_show_uc_one(FILE * fp,
                         struct hit * hp,
                         char * query_head,
                         char * qsequence,
                         long qseqlen,
                         char * rc)
{
  /*
    http://www.drive5.com/usearch/manual/ucout.html

    Columns:
    H/N
    cluster no (0-based) (target sequence no)
    sequence length (query)
    percent identity
    strand: + or -
    0
    0
    compressed alignment, e.g. 9I92M14D
    query label
    target label
  */

  if (hp)
    fprintf(fp,
            "H\t%ld\t%ld\t%.1f\t%c\t0\t0\t%s\t%s\t%s\n",
            hp->target,
            qseqlen,
            hp->internal_id,
            hp->strand ? '-' : '+',
            hp->nwalignment,
            query_head,
            db_getheader(hp->target));
  else
    fprintf(fp, "N\t*\t*\t*\t.\t*\t*\t*\t%s\t*\n", query_head);
}

void results_show_userout_one(FILE * fp, struct hit * hp,
                              char * query_head,
                              char * qsequence, long qseqlen,
                              char * rc)
{

  /* http://drive5.com/usearch/manual/userout.html */

  for (int c = 0; c < userfields_requested_count; c++)
    {
      if (c)
        fprintf(fp, "\t");

      int field = userfields_requested[c];
          
      char * tsequence = 0;
      long tseqlen = 0;
      char * t_head = 0;

      if (hp)
        {
          tsequence = db_getsequence(hp->target);
          tseqlen = db_getsequencelen(hp->target);
          t_head = db_getheader(hp->target);
        }

      char * qrow;
      char * trow;

      switch (field)
        {
        case 0: /* query */
          fprintf(fp, "%s", query_head);
          break;
        case 1: /* target */
          fprintf(fp, "%s", hp ? t_head : "*");
          break;
        case 2: /* evalue */
          fprintf(fp, "-1");
          break;
        case 3: /* id */
          fprintf(fp, "%.1f", hp ? hp->internal_id : 0.0);
          break;
        case 4: /* pctpv */
          fprintf(fp, "%.1f", hp ? 100.0 * hp->matches / hp->internal_alignmentlength : 0.0);
          break;
        case 5: /* pctgaps */
          fprintf(fp, "%.1f", hp ? 100.0 * hp->internal_indels / hp->internal_alignmentlength : 0.0);
          break;
        case 6: /* pairs */
          fprintf(fp, "%ld", hp ? hp->matches + hp->mismatches : 0);
          break;
        case 7: /* gaps */
          fprintf(fp, "%ld", hp ? hp->internal_indels : 0);
          break;
        case 8: /* qlo */
          fprintf(fp, "%ld", hp ? 1L : 0L);
          break;
        case 9: /* qhi */
          fprintf(fp, "%ld", hp ? qseqlen : 0);
          break;
        case 10: /* tlo */
          fprintf(fp, "%ld", hp ? 1L : 0L);
          break;
        case 11: /* thi */
          fprintf(fp, "%ld", hp ? tseqlen : 0);
          break;
        case 12: /* pv */
          fprintf(fp, "%ld", hp ? hp->matches : 0);
          break;
        case 13: /* ql */
          fprintf(fp, "%ld", qseqlen);
          break;
        case 14: /* tl */
          fprintf(fp, "%ld", hp ? tseqlen : 0);
          break;
        case 15: /* qs */
          fprintf(fp, "%ld", hp ? qseqlen : 0);
          break;
        case 16: /* ts */
          fprintf(fp, "%ld", hp ? tseqlen : 0);
          break;
        case 17: /* alnlen */
          fprintf(fp, "%ld", hp ? hp->internal_alignmentlength : 0);
          break;
        case 18: /* opens */
          fprintf(fp, "%ld", hp ? hp->internal_gaps : 0);
          break;
        case 19: /* exts */
          fprintf(fp, "%ld", hp ? hp->internal_indels - hp->internal_gaps : 0);
          break;
        case 20: /* raw */
          fprintf(fp, "%ld", 0L);
          break;
        case 21: /* bits */
          fprintf(fp, "%ld", 0L);
          break;
        case 22: /* aln */ 
          if (hp)
            align_fprint_uncompressed_alignment(fp, hp->nwalignment);
          break;
        case 23: /* caln */
          if (hp)
            fprintf(fp, "%s", hp->nwalignment);
          break;
        case 24: /* qstrand */
          if (hp)
            fprintf(fp, "%c", hp->strand ? '-' : '+');
          break;
        case 25: /* tstrand */
          if (hp)
            fprintf(fp, "%c", '+');
          break;
        case 26: /* qrow */
          if (hp)
            {
              qrow = align_getrow(hp->strand ? rc : qsequence,
                                  hp->nwalignment,
                                  hp->nwalignmentlength,
                                  0);
              fprintf(fp, "%.*s",
                      (int)(hp->internal_alignmentlength),
                      qrow + hp->trim_q_left + hp->trim_t_left);
              free(qrow);
            }
          break;
        case 27: /* trow */
          if (hp)
            {
              trow = align_getrow(tsequence,
                                  hp->nwalignment,
                                  hp->nwalignmentlength,
                                  1);
              fprintf(fp, "%.*s",
                      (int)(hp->internal_alignmentlength),
                      trow + hp->trim_q_left + hp->trim_t_left);
              free(trow);
            }
          break;
        case 28: /* qframe */
          fprintf(fp, "+0");
          break;
        case 29: /* tframe */
          fprintf(fp, "+0");
          break;
        case 30: /* mism */
          fprintf(fp, "%ld", hp ? hp->mismatches : 0);
          break;
        case 31: /* ids */
          fprintf(fp, "%ld", hp ? hp->matches : 0);
          break;
        case 32: /* qcov */
          fprintf(fp, "%.0f",
                  hp ? 100.0 * (hp->matches + hp->mismatches) / qseqlen : 0.0);
          break;
        case 33: /* tcov */
          fprintf(fp, "%.0f",
                  hp ? 100.0 * (hp->matches + hp->mismatches) / tseqlen : 0.0);
          break;
        }
    }
  fprintf(fp, "\n");
}

void results_show_alnout(FILE * fp,
                         struct hit * hits,
                         int hitcount,
                         char * query_head,
                         char * qsequence,
                         long qseqlen,
                         char * rc)
{
  /* http://drive5.com/usearch/manual/alnout.html */

  if (hitcount)
    {
      fprintf(fp, "\n");

      fprintf(fp,"Query >%s\n", query_head);
      fprintf(fp," %%Id   TLen  Target\n");
      
      double top_hit_id = hits[0].internal_id;

      for(int t = 0; t < hitcount; t++)
        {
          struct hit * hp = hits + t;
          
          if (opt_top_hits_only && (hp->internal_id < top_hit_id))
            break;

          fprintf(fp,"%3.0f%% %6lu  %s\n",
                  hp->internal_id,
                  db_getsequencelen(hp->target),
                  db_getheader(hp->target));
        }

      for(int t = 0; t < hitcount; t++)
        {
          struct hit * hp = hits + t;
          
          if (opt_top_hits_only && (hp->internal_id < top_hit_id))
            break;

          fprintf(fp,"\n");
          
          char * dseq = db_getsequence(hp->target);
          long dseqlen = db_getsequencelen(hp->target);
          
          char dummy;
          int qlenlen = snprintf(&dummy, 1, "%ld", qseqlen);
          int tlenlen = snprintf(&dummy, 1, "%ld", dseqlen);
          int numwidth = MAX(qlenlen, tlenlen);
          
          fprintf(fp," Query %*ldnt >%s\n", numwidth,
                  qseqlen, query_head);
          fprintf(fp,"Target %*ldnt >%s\n", numwidth,
                  dseqlen, db_getheader(hp->target));
          
          align_show(fp,
                     qsequence,
                     qseqlen,
                     hp->trim_q_left,
                     "Qry",
                     dseq,
                     dseqlen,
                     hp->trim_t_left,
                     "Tgt",
                     hp->nwalignment + hp->trim_aln_left,
                     strlen(hp->nwalignment) 
                     - hp->trim_aln_left - hp->trim_aln_right,
                     numwidth,
                     3,
                     opt_rowlen,
                     hp->strand);
              
          fprintf(fp,"\n%ld cols, %ld ids (%3.1f%%), %ld gaps (%3.1f%%)",
                  hp->internal_alignmentlength,
                  hp->matches,
                  hp->internal_id,
                  hp->internal_indels,
                  100.0 * hp->internal_indels / hp->internal_alignmentlength);

#if 0
          fprintf(fp," [%ld kmers, %ld score, %ld gap opens]",
                  hp->count, hp->nwscore, hp->nwgaps);
#endif
          fprintf(fp, "\n");
        }
    }
}