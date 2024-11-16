# NAME

vsearch — a versatile open-source tool for metabarcoding and
metagenomics

# SYNOPSIS

**vsearch** \<command\> \[*file*\] \[*options*\]

(see below for a list of available commands)

# DESCRIPTION

vsearch is a versatile open-source tool for microbiome analysis,
including chimera detection, clustering, dereplication and
rereplication, extraction, FASTA/FASTQ/SFF file processing, masking,
orienting, pairwise alignment, restriction site cutting, searching,
shuffling, sorting, subsampling, and taxonomic classification of
amplicon sequences for metabarcoding, metagenomics, genomics, and
population genetics.

# VSEARCH COMMANDS

Each command is described in a dedicated manpage. For example, type
`man vsearch-orient` to read about the orient command. Manpages
reffering to commands all belong to section 1 (executable programs).
Some vsearch manpages belong to section 5 (file formats and
conventions). For example, type `man 5 vsearch-sff` to read about the
SFF format as-seen by vsearch.

## Chimera detection:

**vsearch** (--uchime_denovo \| --uchime2_denovo \| --uchime3_denovo)
*fastafile* (--chimeras \| --nonchimeras \| --uchimealns \| --uchimeout)
*outputfile* \[*options*\]  
**vsearch** --uchime_ref *fastafile* (--chimeras \| --nonchimeras \|
--uchimealns \| --uchimeout) *outputfile* --db *fastafile* \[*options*\]

## Clustering:

**vsearch** (--cluster_fast \| --cluster_size \| --cluster_smallmem \|
--cluster_unoise) *fastafile* (--alnout \| --biomout \| --blast6out \|
--centroids \| --clusters \| --mothur_shared_out \| --msaout \|
--otutabout \| --profile \| --samout \| --uc \| --userout) *outputfile*
--id *real* \[*options*\]

## FASTA/FASTQ/SFF file processing:

**[`vsearch-fasta2fastq(1)`](./commands/vsearch-fasta2fastq.1.md)**  
Convert a fasta file to a fastq file with fake quality scores.

**[`vsearch-fastq_chars(1)`](./commands/vsearch-fastq_chars.1.md)**  
Analyze fastq files to identify the quality encoding and the range of
quality score values used.

## Orienting:

**[`vsearch-orient(1)`](./commands/vsearch-orient.1.md)**  
Use a reference database to orient fastq or fasta sequences.

# FILE FORMATS

**[`vsearch-fasta(5)`](./formats/vsearch-fasta.5.md)**  
Define fasta format, as used by vsearch.

**[`vsearch-fastq(5)`](./formats/vsearch-fastq.5.md)**  
Define fastq format, as used by vsearch.

(also SFF, and UDB).

# SEE ALSO

[swarm](https://github.com/torognes/swarm),
[swipe](https://github.com/torognes/swipe),
[`usearch`](https://github.com/rcedgar/usearch12)

# CITATION

Rognes T, Flouri T, Nichols B, Quince C, Mahé F. (2016) VSEARCH: a
versatile open source tool for metagenomics. **PeerJ** 4:e2584 doi:
[10.7717/peerj.2584](https://doi.org/10.7717/peerj.2584)

# REPORTING BUGS

Submit suggestions and bug-reports at
<https://github.com/torognes/vsearch/issues>, send a pull request on
<https://github.com/torognes/vsearch>, or compose a friendly or
curmudgeont e-mail to Torbjørn Rognes (torognes@ifi.uio.no).

# AVAILABILITY

Source code and binaries are available at
<https://github.com/torognes/vsearch>.

# COPYRIGHT

Copyright (C) 2014-2024, Torbjørn Rognes, Frédéric Mahé and Tomás Flouri

All rights reserved.

Contact: Torbjørn Rognes <torognes@ifi.uio.no>, Department of
Informatics, University of Oslo, PO Box 1080 Blindern, NO-0316 Oslo,
Norway

This software is dual-licensed and available under a choice of one of
two licenses, either under the terms of the GNU General Public License
version 3 or the BSD 2-Clause License.

## GNU General Public License version 3

This program is free software: you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation, either version 3 of the License, or (at your
option) any later version.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
Public License for more details.

You should have received a copy of the GNU General Public License along
with this program. If not, see <http://www.gnu.org/licenses/>.

## The BSD 2-Clause License

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are
met:

1.  Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.

2.  Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS “AS
IS” AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

# ACKNOWLEDGMENTS

We would like to thank the authors of the following projects for making
their source code available:

-   **vsearch** includes code from Google’s CityHash project by Geoff
    Pike and Jyrki Alakuijala, providing some excellent hash functions
    available under a MIT license.
-   **vsearch** includes code derived from Tatusov and Lipman’s DUST
    program that is in the public domain.
-   **vsearch** includes public domain code written by Alexander Peslyak
    for the MD5 message digest algorithm.
-   **vsearch** includes public domain code written by Steve Reid and
    others for the SHA1 message digest algorithm.
-   **vsearch** binaries may include code from the zlib library,
    copyright Jean-Loup Gailly and Mark Adler.
-   **vsearch** binaries may include code from the bzip2 library,
    copyright Julian R. Seward.

# VERSION HISTORY

(inject history here)
