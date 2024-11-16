# NAME

vsearch --fastq_chars — analyze fastq files to identify the quality
encoding and the range of quality score values used.

# SYNOPSIS

**vsearch** **--fastq_chars** *fastqfile* \[*options*\]

# DESCRIPTION

The `vsearch --fastq_chars` command summarizes the number and
composition of sequences and quality strings contained in the input
fastq file. Results are written to the standard error, and to *filename*
if option `--log` *filename* is used.

For each sequence symbol, `--fastq_chars` gives the number of
occurrences of the symbol, its relative frequency and the length of the
longest run of that symbol (lowercase symbols are converted to
uppercase). For each quality symbol, `--fastq_chars` gives the ASCII
value of the symbol, its relative frequency, and the number of times a
*k*-mer of that symbol appears at the end of quality strings. The length
of the *k*-mer can be set with the option `--fastq_tail` (4 by default).

The command `--fastq_chars` tries to automatically detect the quality
encoding (Solexa, Illumina 1.3+, Illumina 1.5+ or Illumina 1.8+/Sanger)
by analyzing the range of observed quality score values. In case of
success, `--fastq_chars` suggests values for the `--fastq_ascii` (33 or
64), as well as `--fastq_qmin` and `--fastq_qmax` values to be used with
the other commands that require a fastq input file. If the quality
encoding is ambiguous, `--fastq_chars` will favor an offset of 33.

# OPTIONS

## core options

`--fastq_tail` *positive non-null integer*  
Count the number of times a series of characters of length *k* =
*positive non-null integer*, a *k*-mer, appears at the end of quality
strings. By default, *k* = 4.

## secondary options

`--bzip2_decompress`  
When reading from a pipe streaming bzip2-compressed data, decompress the
data. This option is not needed when reading from a standard
bzip2-compressed file.

`--gzip_decompress`  
When reading from a pipe streaming gzip-compressed data, decompress the
data. This option is not needed when reading from a standard
gzip-compressed file.

`--log` *filename*  
Write messages to *filename*. Information includes program version,
start and finish times, elapsed time, amount of memory available,
maximum amount of memory consumed, number of cores and command line
options, and if need be, informational messages, warnings and fatal
errors.

A copy of the statistics computed by `--fastq_chars` is also recorded.

`--no_progress`  
Do not show the gradually increasing progress indicator.

`--quiet`  
Suppress all messages to the standard output (`stdout`) and standard
error (`stderr`), except for warnings and fatal error messages.

`--threads` *positive non-null integer*  
Command is not multithreaded. Option `--threads` is accepted but has no
effect.

# EXAMPLES

Read from *input.fastq*, count *5*-mers at the end of quality strings
(`--fastq_tail 5`), do not write to the standard error (`--quiet`), and
write results to *output.log* (`--log`):

``` sh
vsearch \
    --fastq_chars input.fastq \
    --fastq_tail 5 \
    --quiet \
    --log output.log
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
