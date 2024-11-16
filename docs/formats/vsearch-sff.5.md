# NAME

sff — a binary file format used to encode pyrosequencing results

# DESCRIPTION

Standard flowgram format (sff), used by Roche 454 and Ion Torrent PGM

(complete description of the SFF format, hard to find on the web)

A sff file must start with a 31-byte common header: - magic value: a
32-bit value spelling ‘.sff’ (0x2e736666), - version value: a 32-bit
value set to 1 (0x00000001) - index offset: a 64-bit value - index
length: a 32-bit value - number of reads: a 32-bit value - header
length: a 16-bit value - key length: a 16-bit value - flow length: a
16-bit value - flowgram format: a 8-bit value

sff files are in big endian notation (no known counter-example)

from
https://web.archive.org/web/20190113035506/https://www.ncbi.nlm.nih.gov/Traces/trace.cgi?view=doc_formats#sffhere

Standard Flowgram Format (SFF)

SFF was designed by 454 Life Sciences, Whitehead Institute for
Biomedical Research and Sanger Institute.

The proposed SFF file format is a container file for storing one or many
454 reads. 454 reads differ from standard sequencing reads in that the
454 data does not provide individual base measurements from which
basecalls can be derived. Instead, it provides measurements that
estimate the length of the next homopolymer stretch in the sequence
(i.e., in “AAATGG”, “AAA” is a 3-mer stretch of A’s, “T” is a 1-mer
stretch of T’s and “GG” is a 2-mer stretch of G’s). A basecalled
sequence is then derived by converting each estimate into a homopolymer
stretch of that length and concatenating the homopolymers.

The file format consists of three sections, a *common header* section
occurring once in the file, then for each read stored in the file, a
*read header* section and a *read data* section. The data in each
section consists of a combination of numeric and character data, where
the specific fields for each section are defined below. The sections
adhere to the following rules:

-   The standard Unix types uint8_t, uint16_t, uint32_t and uint64_t are
    used to define 1, 2, 4 and 8 byte numeric values.
-   All multi-byte numeric values are stored using big endian byteorder
    (same as the SCF file format).
-   All character fields use single-byte ASCII characters.
-   Each section definition ends with an “eight_byte_padding” field,
    which consists of 0 to 7 bytes of padding, so that the length of
    each section is divisible by 8 (and hence the next section is
    aligned on an 8-byte boundary).

## Common Header Section

The common header section consists of the following fields:

-   `magic_number` `uint32_t`
-   `version` `char[4]`
-   `index_offset` `uint64_t`
-   `index_length` `uint32_t`
-   `number_of_reads` `uint32_t`
-   `header_length` `uint16_t`
-   `key_length` `uint16_t`
-   `number_of_flows_per_read` `uint16_t`
-   `flowgram_format_code` `uint8_t`
-   `flow_chars` `char[number_of_flows_per_read]`
-   `key_sequence` `char[key_length]`
-   `eight_byte_padding` `uint8_t[*]`

where the following properties are true for these fields:

-   The `magic_number` field value is 0x2E736666, the `uint32_t`
    encoding of the string “.sff”
-   The version number corresponding to this proposal is 0001, or the
    byte array “\\0\\0\\0\\1”.
-   The `index_offset` and `index_length` fields are the offset and
    length of an optional index of the reads in the SFF file. If no
    index is included in the file, both fields must be 0.
-   The `number_of_reads` field should be set to the number of reads
    stored in the file.
-   The `header_length` field should be the total number of bytes
    required by this set of header fields, and should be equal to “31 +
    `number_of_flows_per_read` + `key_length`” rounded up to the next
    value divisible by 8.
-   The `key_length` and `key_sequence` fields should be set to the
    length and nucleotide bases of the key sequence used for these
    reads. Note: The `key_sequence` field is not null-terminated.
-   The `number_of_flows_per_read` should be set to the number of flows
    for each of the reads in the file.
-   The `flowgram_format`\_code should be set to the format used to
    encode each of the flowgram values for each read.
    -   Note: Currently, only one flowgram format has been adopted, so
        this value should be set to 1.
    -   The flowgram format code 1 stores each value as a uint16_t,
        where the floating point flowgram value is encoded as “(int)
        round(value \* 100.0)”, and decoded as “(storedvalue \* 1.0 /
        100.0)”.
-   The `flow_chars` should be set to the array of nucleotide bases
    (‘A’, ‘C’, ‘G’ or ‘T’) that correspond to the nucleotides used for
    each flow of each read. The length of the array should equal
    `number_of_flows_per_read`.
    -   Note: The flow_chars field is not null-terminated.
-   If any `eight_byte`\_padding bytes exist in the section, they should
    have a byte value of 0.

If an index is included in the file, the `index_offset` and
`index_length` values in the common header should point to the section
of the file containing the index. To support different indexing methods,
the index section should begin with the following two fields:

-   `index_magic_number` uint32_t
-   `index_version` char\[4\]

and should end with an `eight_byte_padding` field, so that the length of
the index section is divisible by 8. The format of the rest of the index
section is specific to the indexing method used. The index_length given
in the common header should include the bytes of these fields and the
padding.

Note: Currently, there are no officially supported indexing formats,
however support for the `io_lib` hash table indexing and a simple sorted
list indexing should be developed shortly.

## Read Header Section

The rest of the file contains the information about the reads, namely
`number_of_reads` entries consisting of read header and read data
sections. The read header section consists of the following fields:

    read_header_length         uint16_t

    name_length                uint16_t

    number_of_bases            uint32_t

    clip_qual_left             uint16_t

    clip_qual_right            uint16_t

    clip_adapter_left          uint16_t

    clip_adapter_right         uint16_t

    name                       char[name_length]

    eight_byte_padding         uint8_t[*]

where these fields have the following properties:

    The read_header_length should be set to the length of the read header for this read, and should be equal to "16 + name_length" rounded up to the next value divisible by 8.
    The name_length and name fields should be set to the length and string of the read's accession or name.
        Note: The name field is not null-terminated.
    The number_of_bases should be set to the number of bases called for this read.
    The clip_qual_left and clip_adapter_left fields should be set to the position of the first base after the clipping point, for quality and/or an adapter sequence, at the beginning of the read. If only a combined clipping position is computed, it should be stored in clip_qual_left.
        The position values use 1-based indexing, so the first base is at position 1.
        If a clipping value is not computed, the field should be set to 0.
        Thus, the first base of the insert is "max(1, max(clip_qual_left, clip_adapter_left))".
    The clip_qual_right and clip_adapter_right fields should be set to the position of the last base before the clipping point, for quality and/or an adapter sequence, at the end of the read. If only a combined clipping position is computed, it should be stored in clip_qual_right.
        The position values use 1-based indexing.
        If a clipping value is computed, the field should be set to 0.
        Thus, the last base of the insert is "min( (clip_qual_right == 0 ? number_of_bases : clip_qual_right), (clip_adapter_right == 0 ? number_of_bases : clip_adapter_right) )".

## Read Data Section

The read data section consists of the following fields:

    flowgram_values            uint*_t[number_of_flows]

    flow_index_per_base        uint8_t[number_of_bases]

    bases                      char[number_of_bases]

    quality_scores             uint8_t[number_of_bases]

    eight_byte_padding         uint8_t[*]

where the fields have the following properties:

    The flowgram_values field contains the homopolymer stretch estimates for each flow of the read. The number of bytes used for each value depends on the common header flowgram_format_code value (where the current value uses a uint16_t for each value).
    The flow_index_per_base field contains the flow positions for each base in the called sequence (i.e., for each base, the position in the flowgram whose estimate resulted in that base being called).
        These values are "incremental" values, meaning that the stored position is the offset from the previous flow index in the field.
        All position values (prior to their incremental encoding) use 1-based indexing, so the first flow is flow 1.
    The bases field contains the basecalled nucleotide sequence.
    The quality_scores field contains the quality scores for each of the bases in the sequence, where the values use the standard -log10 probability scale.

## Computing Lengths and Scanning the File

The length of each read’s section will be different, because of
different length accession numbers and different length nucleotide
sequences. However, the various flow, name and bases lengths given in
the common and read headers can be used to scan the file, accessing each
read’s information or skipping read sections in the file. The following
pseudocode gives an example method to scanning the file and accessing
each read’s data:

    Open the file and/or reset the file pointer position to the first byte of the file.
    Read the first 31 bytes of the file, confirm the magic_number value and version, then extract the number_of_reads, number_of_flows_per_read, flowgram_format_code, header_length, key_length, index_offset and index_length values.
        Convert the flowgram_format_code into a flowgram_bytes_per_flow value (currently with format_code 1, this value is 2 bytes).
    If the flow_chars and key_sequence information is required, read the next "header_length - 31" bytes, then extract that information. Otherwise, set the file pointer position to byte header_length.
    While the file contains more bytes, do the following:
        If the file pointer position equals index_offset, either read or skip index_length bytes in the file, processing the index if read.
        Otherwise,
            Read 16 bytes and extract the read_header_length, name_length and number_of_bases values.
            Read the next "read_header_length - 16" bytes to read the name.
            At this point, a test of the name field can be perform, to determine whether to read or skip this entry.
            Compute the read_data_length as "number_of_flows * flowgram_bytes_per_flow + 3 * number_of_bases" rounded up to the next value divisible by 8.
            Either read or skip read_data_length bytes in the file, processing the read data if the section is read.

end of the NCBI documentation

# EXAMPLES

(show how to build sff files?)

# SEE ALSO

[`vsearch-fasta(5)`](./vsearch-fasta.5.md),
[`vsearch-fastq(5)`](./vsearch-fastq.5.md)

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
