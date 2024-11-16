# NAME

vsearch --orient — use a reference database to orient fastq or fasta
sequences

# SYNOPSIS

**vsearch** **--orient** *fastxfile* --db *fastxfile* (--fastaout \|
--fastqout \| --notmatched \| --tabbedout) *outputfile* \[*options*\]

# DESCRIPTION

The `vsearch --orient` command can be used to orient the sequences in a
given fastq or fasta file in either the forward or the reverse
complementary direction based on a reference database specified with the
`--db` option. The two strands of each input sequence are compared to
the reference database using nucleotide words. If one of the strands
shares 4 times (or more) words with any sequence in the database than
the other strand, then it is chosen.

# OPTIONS

`--db` is mandatory, and at least one of `--fastaout`, `--fastqout`,
`--notmatched`, `--tabbedout` must also be specified.

## core options

`--db` *filename*  
Read the reference database from the given fasta, fastq, or UDB
*filename*. Only UDB files created with a `--wordlength` of 12 are
accepted (see
[`vsearch-makeudb_usearch(1)`](./vsearch-makeudb_usearch.1.md) for more
details).

`--fastaout` *filename*  
Write the correctly oriented sequences to *filename*, in fasta format.

`--fastqout` *filename*  
Write the correctly oriented sequences to *filename*, in fastq format
(requires a fastq input file).

`--notmatched` *filename*  
Write the sequences with undetermined direction to *filename*, in the
original format.

`--tabbedout` *filename*  
Write the resuls to a four-column tab-delimited file with the specified
*filename*. Columns are:

1.  query label
2.  direction (+, -, or ?)
3.  number of matching words on the forward strand
4.  number of matching words on the reverse complementary strand

## secondary options

`--bzip2_decompress`  
When reading from a pipe streaming bzip2-compressed data, decompress the
data. This option is not needed when reading from a standard
bzip2-compressed file.

`--fasta_width` *positive integer*  
Fasta files produced by `vsearch` are wrapped (sequences are written on
lines of *positive integer* nucleotides, 80 by default). Set the value
to zero to eliminate the wrapping.

`--dbmask` *none*\|*dust*\|*soft*  
Mask regions in the database sequences using the *dust* method or the
*soft* method, or do not mask (*none*). Warning, when using *soft*
masking, search commands become case sensitive. The default is to mask
using *dust*.

`--gzip_decompress`  
When reading from a pipe streaming gzip-compressed data, decompress the
data. This option is not needed when reading from a standard
gzip-compressed file.

`--label_suffix` *string*  
When writing fasta or fastq files, add the suffix *string* to sequence
headers.

`--lengthout`  
Write sequence length information to the output files in FASTA and FASTQ
format by adding a `;length=integer` attribute in the header.

`--log` *filename*  
Write messages to *filename*. Information includes program version,
start and finish times, elapsed time, amount of memory available,
maximum amount of memory consumed, number of cores and command line
options, and if need be, informational messages, warnings and fatal
errors.

`--no_progress`  
Do not show the gradually increasing progress indicator.

`--notrunclabels`  
Do not truncate sequence labels at first space or tab, but use the full
header in output files.

`--qmask` *none*\|*dust*\|*soft*  
Mask regions in query sequences using the *dust* method or the *soft*
method, or do not mask (*none*). Warning, when using *soft* masking,
search commands become case sensitive. The default is to mask using
*dust*.

`--quiet`  
Suppress all messages to the standard output (`stdout`) and standard
error (`stderr`), except for warnings and fatal error messages.

`--relabel` *string*  
Relabel sequences using the prefix *string* and a ticker (1, 2, 3, etc.)
to construct the new headers. Use `--sizeout` to conserve the abundance
annotations.

`--relabel_keep`  
When relabelling, keep the old identifier in the header after a space.

`--relabel_md5`  
Relabel sequences using the MD5 message digest algorithm applied to each
sequence. Former sequence headers are discarded. The sequence is
converted to upper case and each ‘U’ is replaced by a ‘T’ before
computation of the digest.

The MD5 digest is a cryptographic hash function designed to minimize the
probability that two different inputs give the same output, even for
very similar, but non-identical inputs. Still, there is a very small,
but non-zero, probability that two different inputs give the same digest
(i.e. a collision). MD5 generates a 128-bit (16-byte) digest that is
represented by 16 hexadecimal numbers (using 32 symbols among
0123456789abcdef). Use `--sizeout` to conserve the abundance
annotations.

`--relabel_self`  
Relabel sequences using each sequence itself as a label.

`--relabel_sha1`  
Relabel sequences using the SHA1 message digest algorithm applied to
each sequence. It is similar to the `--relabel_md5` option but uses the
SHA1 algorithm instead of the MD5 algorithm. SHA1 generates a 160-bit
(20-byte) digest that is represented by 20 hexadecimal numbers (40
symbols). The probability of a collision (two non-identical sequences
resulting in the same digest) is smaller for the SHA1 algorithm than it
is for the MD5 algorithm. Use `--sizeout` to conserve the abundance
annotations.

`--sample` *string*  
When writing fasta or fastq files, add the the given sample identifier
*string* to sequence headers. For instance, if *string* is ‘ABC’, the
text `;sample=ABC` will be added to the header. Note that *string* will
be truncated at the first ‘;’ or blank character. Other characters
(alphabetical, numerical and punctuations) are accepted.

`--sizein`  
Take into account the abundance annotations present in the input fastq
or fasta file (search for the pattern `[>;]size=integer[;]` in sequence
headers).

`--sizeout`  
Add abundance annotations to the output fastq or fasta files (add the
pattern `;size=integer;` to sequence headers). If option `--sizein` is
not used, abundances values are set to 1. If `--sizein` is used,
existing abundance annotations are simply reported to output files.

`--threads` *positive non-null integer*  
Command is not multithreaded. Option `--threads` is accepted but has no
effect.

`--xee`  
Strip expected error (ee) annotations from fastq or fasta headers when
writing output files (find and remove the pattern `;ee=float[;]` from
sequence headers). Expected error annotations are added by the
synonymous options `--fastq_eeout` and `--eeout` (see for example
command `--fastx_filter`).

`--xlength`  
Strip sequence length annotations from fastq or fasta headers when
writing output files (find and remove the pattern `;length=integer[;]`
from sequence headers). Sequence length annotations are added by the
`--lengthout` option (see for example the command `--fastq_join`).

`--xsize`  
Strip abundance annotations from fastq or fasta headers when writing
output files (find and remove the pattern `;size=integer[;]` from
sequence headers). Abundance annotations are added by the `--sizeout`
option (see for example the command `--derep_fulllength`).

# EXAMPLES

Use the sequences in *db.fastq* to orient the sequences in
*query.fastq*. Write the results to *query_oriented.fasta*, in fasta
format:

``` sh
vsearch \
    --orient query.fastq \
    --db db.fastq \
    --fastaout query_oriented.fasta
```

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
