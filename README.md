# Amplification Channel Optimization Problem (ACOP)

This repository represents an electronic supplement to the following paper:

| Carina Heßeling, Jörg Keller, and Steffen Wendzel: *Optimized DYST-like Amplification Covert Channel*, In Proc. ARES 2026 Workshops / IWAPS Workshop, 2026. |
|----|

## Explanatory note on the calculation table

This spreadsheet [IWAPS-Example-Textdata](https://github.com/cdpxe/ACOP/blob/main/IWAPS-Example-Textdata.xlsx) accompanies the numerical example in Section 4 of our paper.
The spreadsheet is intended as a reproducibility aid for readers who want to inspect how the packet counts reported in the article have been obtained from the assumptions stated in the article. The table does not introduce a separate model. It just expands the calculations behind the example.

The source alphabet consists of 40 symbols following a Zipf distribution, to reflect a distribution found in texts. The table first computes the normalizing constant from the 40th harmonic number and derives the individual source probabilities. These probabilities are then used to compute the entropy of the source. The entropy value is compared with the average length of the near-Huffman encoding used in the example.

The encoding used in the example maps the more frequent source symbols to shorter codewords (4 bit) and the remaining source symbols to longer codewords (6 bit). Since the carrier alphabet consists of four 2-bit symbols, the codewords are evaluated in terms of how often each of these four carrier symbols occurs. The count columns in the spreadsheet therefore represent occurrences of the four 2-bit carrier symbols within the assigned codewords. From these counts and the source probabilities, the expected encoded-symbol distribution $q_i$ is derived.

The carrier-symbol distribution $p_i$ is based on the selected ToS values from the MAWI trace used in the example. The most frequent ToS value (0x00) is intentionally excluded, as stated in the article. The next 4 (2nd to 5th most frequent) values are normalized over the four carrier symbols considered in the calculation. Thus, the $p_i$ values in the spreadsheet should be read as the carrier distribution after this selection step, i.e., as the probabilities of the extracted carrier symbols, not as frequencies over all observed ToS values.

The final expected number of observed packets follows Equation (3) in the paper. The relevant term is

$\bar{L} \cdot \sum_i(q_i / p_i)$,

where $\bar{L}$ is the average number of 2-bit carrier symbols per original source symbol, $q_i$ is the expected distribution of encoded message symbols, and $p_i$ is the selected carrier-symbol distribution. The result is an expected packet count per original message symbol, not per encoded 2-bit symbol.

One detail that is easy to miss is that the pairing of $q_i$ and $p_i$ matters. The sum depends on which encoded-symbol frequency is assigned to which carrier-symbol probability. In the article, both $q_i$ and $p_i$ are sorted in descending order, which achieves a suitable pairing.
The spreadsheet uses the assignment underlying the example in the article, which pairs the encoded-symbol distribution with the selected carrier distribution in the order that yields the reported value. This leads to approximately 9.23 observed packets per original message symbol, between the lower bound of approximately 8.76 and the upper bound of approximately 9.46.
