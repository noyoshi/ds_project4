Project 04 - Key-Value Store II
===============================

Group Dynamics
===
## Group Members
- Noah Yoshida (nyoshida, Section 02)
    - Derp

- Timothy Blazek (tblazek, Section 02)
    - Helped debug the backends, and worked on unordered mapping and chained mapping
    - Formatted and answered questions on README

- Edward Atkinson (eatkins1, Section 02)
    - Helped with the debugging process
    - Created fully automated python scripts for both benchmarking and
      frequencies, which when run generate a fully completed markdown table


Backend Analysis
===
## Unordered

### Average
Search: O(1)
Insert: O(1)

### Worst
Search: O(n)
Insert: O(n)

On average, the key-value pairs will be spread across different buckets, however, in the worst case they are all put in the same bucket and then there is O(n) search and insert.

## Chained

### Average
Search: O(1)
Insert: O(1)

### Worst
Search: O(n)
Insert: O(n)

Ideally, all the key-value pairs will be spread across different hashes, so the average is O(1), however, it is possible that they all get hashed to the same list, in which case the insertion and search would be O(n).

## Open

### Average
Search: O(1)
Insert: O(1)

### Worst
Search: O(n)
Insert: O(n)

In the average case, everything would get hashed to a different spot and so on average, there are little to no collisions. Hence, we have constant time for search and insert. However, if we get a bad hash function that puts assigns everything to the same bucket, then we will need to traverse each consecutive bucket to find or insert a key-value pair.

Benchmarks
===

|    BACKEND    |  NITEMS  |   INSERT   |   SEARCH   |
|---------------|----------|------------|------------|
|       unsorted|        10|  2.0133e-05|   8.977e-06|
|       unsorted|       100|  0.00020507|   2.587e-05|
|       unsorted|      1000|    0.016251|  0.00020548|
|       unsorted|     10000|      1.5842|   0.0019249|
|       unsorted|    100000|         inf|    0.019733|
|       unsorted|   1000000|         inf|      0.2032|
|       unsorted|  10000000|         inf|      4.0455|
|         sorted|        10|  3.0708e-05|  1.2503e-05|
|         sorted|       100|  0.00043494|  4.9973e-05|
|         sorted|      1000|    0.031432|  0.00042745|
|         sorted|     10000|      2.9837|   0.0041911|
|         sorted|    100000|         inf|    0.045044|
|         sorted|   1000000|         inf|     0.45937|
|         sorted|  10000000|         inf|      6.2817|
|            bst|        10|  2.3261e-05|  1.5705e-05|
|            bst|       100|  0.00011963|  4.8552e-05|
|            bst|      1000|   0.0013648|  0.00039645|
|            bst|     10000|    0.039309|   0.0041288|
|            bst|    100000|     0.35842|    0.077478|
|            bst|   1000000|      2.9062|     0.42096|
|            bst|  10000000|      28.402|      5.6504|
|         rbtree|        10|  3.1399e-05|  1.4181e-05|
|         rbtree|       100|  0.00016448|  5.6454e-05|
|         rbtree|      1000|   0.0017335|  0.00047052|
|         rbtree|     10000|    0.039588|   0.0045024|
|         rbtree|    100000|     0.23317|    0.048582|
|         rbtree|   1000000|      3.3826|     0.53818|
|         rbtree|  10000000|      36.675|       6.022|
|          treap|        10|  2.8627e-05|  1.6129e-05|
|          treap|       100|  0.00013876|  5.0495e-05|
|          treap|      1000|   0.0012636|   0.0004023|
|          treap|     10000|    0.024032|   0.0041529|
|          treap|    100000|     0.36509|    0.067286|
|          treap|   1000000|      2.2286|     0.65587|
|          treap|  10000000|      27.667|      5.5122|
|      unordered|        10|  3.3707e-05|  1.8439e-05|
|      unordered|       100|  0.00012011|   6.661e-05|
|      unordered|      1000|   0.0010013|  0.00052431|
|      unordered|     10000|   0.0098198|   0.0051301|
|      unordered|    100000|     0.19624|    0.086906|
|      unordered|   1000000|      1.6611|     0.79715|
|      unordered|  10000000|      19.379|      7.1537|
|    chained-0.5|        10|  2.2941e-05|  1.7203e-05|
|    chained-0.5|       100|  9.3797e-05|  5.3289e-05|
|    chained-0.5|      1000|    0.010261|  0.00047226|
|    chained-0.5|     10000|    0.077011|   0.0043544|
|    chained-0.5|    100000|     0.60308|    0.057642|
|    chained-0.5|   1000000|      3.3725|     0.58568|
|    chained-0.5|  10000000|      48.294|      7.0944|
|   chained-0.75|        10|  2.4613e-05|  1.1964e-05|
|   chained-0.75|       100|  0.00010637|  5.5984e-05|
|   chained-0.75|      1000|   0.0027115|  0.00045051|
|   chained-0.75|     10000|     0.05526|    0.004394|
|   chained-0.75|    100000|     0.72186|    0.090588|
|   chained-0.75|   1000000|      3.6319|     0.52924|
|   chained-0.75|  10000000|       35.77|      5.7915|
|    chained-1.0|        10|  2.4313e-05|  1.4816e-05|
|    chained-1.0|       100|  0.00010288|  5.2114e-05|
|    chained-1.0|      1000|  0.00099846|   0.0004512|
|    chained-1.0|     10000|     0.05025|   0.0044669|
|    chained-1.0|    100000|     0.35907|    0.057607|
|    chained-1.0|   1000000|      3.0644|     0.92743|
|    chained-1.0|  10000000|      40.925|      6.9181|
|    chained-5.0|        10|  2.5226e-05|  1.2139e-05|
|    chained-5.0|       100|  9.8561e-05|  5.2848e-05|
|    chained-5.0|      1000|     0.00101|  0.00045487|
|    chained-5.0|     10000|    0.021179|   0.0045127|
|    chained-5.0|    100000|     0.33934|    0.086605|
|    chained-5.0|   1000000|       3.381|     0.51655|
|    chained-5.0|  10000000|      31.728|      5.5977|
|   chained-10.0|        10|  2.1578e-05|  1.6572e-05|
|   chained-10.0|       100|  0.00010425|  5.4422e-05|
|   chained-10.0|      1000|    0.001123|  0.00045457|
|   chained-10.0|     10000|    0.025129|   0.0044746|
|   chained-10.0|    100000|     0.41859|    0.045123|
|   chained-10.0|   1000000|      3.8682|     0.51031|
|   chained-10.0|  10000000|      35.004|      6.1769|
|  chained-100.0|        10|  2.4054e-05|  1.5509e-05|
|  chained-100.0|       100|  0.00010282|  5.2127e-05|
|  chained-100.0|      1000|   0.0011244|  0.00045978|
|  chained-100.0|     10000|    0.024877|   0.0043919|
|  chained-100.0|    100000|     0.29488|    0.084114|
|  chained-100.0|   1000000|      5.9902|     0.76505|
|  chained-100.0|  10000000|      52.596|      6.5703|
|       open-0.5|        10|  2.0022e-05|  1.3761e-05|
|       open-0.5|       100|  7.1857e-05|  6.3656e-05|
|       open-0.5|      1000|   0.0015279|  0.00052786|
|       open-0.5|     10000|    0.036342|   0.0051073|
|       open-0.5|    100000|     0.28994|     0.10307|
|       open-0.5|   1000000|      2.4355|     0.70302|
|       open-0.5|  10000000|      31.587|      7.3261|
|       open-0.6|        10|  1.5692e-05|  1.3189e-05|
|       open-0.6|       100|  7.3244e-05|  6.0485e-05|
|       open-0.6|      1000|   0.0016001|  0.00050384|
|       open-0.6|     10000|     0.05081|    0.005229|
|       open-0.6|    100000|     0.27735|    0.073512|
|       open-0.6|   1000000|      2.7233|     0.86747|
|       open-0.6|  10000000|      22.233|      7.1895|
|       open-0.7|        10|  1.8833e-05|  2.5921e-05|
|       open-0.7|       100|  7.5186e-05|  6.8633e-05|
|       open-0.7|      1000|     0.00171|  0.00056234|
|       open-0.7|     10000|    0.024451|   0.0050929|
|       open-0.7|    100000|      0.2304|      0.1111|
|       open-0.7|   1000000|      2.5021|     0.62005|
|       open-0.7|  10000000|       22.25|      7.4173|
|       open-0.8|        10|  2.0366e-05|  1.3639e-05|
|       open-0.8|       100|  7.2821e-05|  6.0267e-05|
|       open-0.8|      1000|   0.0018255|  0.00052328|
|       open-0.8|     10000|    0.028579|   0.0052721|
|       open-0.8|    100000|     0.15409|    0.087442|
|       open-0.8|   1000000|      2.5779|     0.62104|
|       open-0.8|  10000000|      23.363|      7.1297|
|       open-0.9|        10|  1.6161e-05|  1.3663e-05|
|       open-0.9|       100|  7.7668e-05|   5.921e-05|
|       open-0.9|      1000|    0.001969|  0.00054736|
|       open-0.9|     10000|    0.032315|    0.005387|
|       open-0.9|    100000|     0.20697|     0.11124|
|       open-0.9|   1000000|      2.5728|      0.7481|
|       open-0.9|  10000000|      23.954|      6.6436|
|       open-1.0|        10|  1.5528e-05|  1.3711e-05|
|       open-1.0|       100|  7.6922e-05|  6.3406e-05|
|       open-1.0|      1000|   0.0013127|  0.00052102|
|       open-1.0|     10000|         inf|   0.0052281|
|       open-1.0|    100000|         inf|     0.10098|
|       open-1.0|   1000000|         inf|     0.92804|
|       open-1.0|  10000000|         inf|      10.526|

Frequencies
===

|  Backend  |         Text          | File Size |    Elapsed Time    |      Memory      |
|-----------|-----------------------|-----------|--------------------|------------------|
|   unsorted|  heart\_of\_darkness.txt|   233531 B|    6.302319 seconds|   4.023438 Mbytes|
|     sorted|  heart\_of\_darkness.txt|   233531 B|    7.354267 seconds|   4.070312 Mbytes|
|        bst|  heart\_of\_darkness.txt|   233531 B|    0.115442 seconds|   4.214844 Mbytes|
|     rbtree|  heart\_of\_darkness.txt|   233531 B|    0.143937 seconds|   4.351562 Mbytes|
|      treap|  heart\_of\_darkness.txt|   233531 B|    0.133658 seconds|   4.210938 Mbytes|
|  unordered|  heart\_of\_darkness.txt|   233531 B|    0.076280 seconds|   4.292969 Mbytes|
|    chained|  heart\_of\_darkness.txt|   233531 B|    0.099494 seconds|   8.734375 Mbytes|
|       open|  heart\_of\_darkness.txt|   233531 B|    0.085701 seconds|   9.046875 Mbytes|
|   unsorted|      metamorphosis.txt|   141450 B|    1.822316 seconds|   3.562500 Mbytes|
|     sorted|      metamorphosis.txt|   141450 B|    2.175287 seconds|   3.605469 Mbytes|
|        bst|      metamorphosis.txt|   141450 B|    0.067584 seconds|   3.726562 Mbytes|
|     rbtree|      metamorphosis.txt|   141450 B|    0.080264 seconds|   3.839844 Mbytes|
|      treap|      metamorphosis.txt|   141450 B|    0.073211 seconds|   3.734375 Mbytes|
|  unordered|      metamorphosis.txt|   141450 B|    0.044674 seconds|   3.828125 Mbytes|
|    chained|      metamorphosis.txt|   141450 B|    0.064654 seconds|   8.242188 Mbytes|
|       open|      metamorphosis.txt|   141450 B|    0.059288 seconds|   9.062500 Mbytes|
|   unsorted|              bible.txt|  4452098 B|  196.639526 seconds|   7.140625 Mbytes|
|     sorted|              bible.txt|  4452098 B|  600.761963 seconds|   7.015625 Mbytes|
|        bst|              bible.txt|  4452098 B|    2.065292 seconds|   6.371094 Mbytes|
|     rbtree|              bible.txt|  4452098 B|    2.666473 seconds|   6.953125 Mbytes|
|      treap|              bible.txt|  4452098 B|    2.502044 seconds|   6.339844 Mbytes|
|  unordered|              bible.txt|  4452098 B|    1.398714 seconds|   6.726562 Mbytes|
|    chained|              bible.txt|  4452098 B|    1.581267 seconds|  80.015625 Mbytes|
|       open|              bible.txt|  4452098 B|    1.537058 seconds|  99.195312 Mbytes|
|   unsorted|           sherlock.txt|   594941 B|   19.135134 seconds|   3.988281 Mbytes|
|     sorted|           sherlock.txt|   594941 B|   31.753948 seconds|   4.042969 Mbytes|
|        bst|           sherlock.txt|   594941 B|    0.279676 seconds|   4.710938 Mbytes|
|     rbtree|           sherlock.txt|   594941 B|    0.345151 seconds|   4.921875 Mbytes|
|      treap|           sherlock.txt|   594941 B|    0.324438 seconds|   4.613281 Mbytes|
|  unordered|           sherlock.txt|   594941 B|    0.184182 seconds|   4.839844 Mbytes|
|    chained|           sherlock.txt|   594941 B|    0.268033 seconds|  23.832031 Mbytes|
|       open|           sherlock.txt|   594941 B|    0.237282 seconds|  27.144531 Mbytes|
|   unsorted|              iliad.txt|  1201883 B|   78.923630 seconds|   5.062500 Mbytes|
|     sorted|              iliad.txt|  1201883 B|   99.552567 seconds|   5.070312 Mbytes|
|        bst|              iliad.txt|  1201883 B|    0.559419 seconds|   5.691406 Mbytes|
|     rbtree|              iliad.txt|  1201883 B|    0.671491 seconds|   6.128906 Mbytes|
|      treap|              iliad.txt|  1201883 B|    0.625732 seconds|   5.804688 Mbytes|
|  unordered|              iliad.txt|  1201883 B|    0.345671 seconds|   5.867188 Mbytes|
|    chained|              iliad.txt|  1201883 B|    0.425037 seconds|  24.679688 Mbytes|
|       open|              iliad.txt|  1201883 B|    0.380233 seconds|  27.164062 Mbytes|


Discussion
===
Looking at the second table, it is apparent that the unordered map implementation outperformed chained and open, with it having 
faster execution and better memory usage. Then the unordered and the chained implementations had little advantages and disadvantages
between each other because the chained was more memory efficient, but the open addressing implementation was slightly faster. The 
differences probably occur because we initialize each bucket to have a large list in the chained implementation and for the open 
implementation, a lot of memory is used because we need a lot of buckets such that each key, value pair has its own. 

As NITEMS increased, unsurprisingly, the insertion and search times increased because there were more items that had to be parsed through.
As load factor increased, the times actually start to decrease, but at some point the times start to increase, this suggests that there
is some sort of optimal load-factor for these implementations. For chained it would be around 5, while for open it would be around 0.5. Lastly
as the file sizes got bigger, the times also increased, which is also not too surprising considering that there is more items to insert and search
through.

Out of all eight of the backends, it seems like the unordered implementation is the best. It has the lowest elapsed time when going 
through the texts, and it was pretty close in memory usage as others that are lower. When comparing the insertion and search times, the 
insertion times were reasonably lower than others, while the search times were slightly slower than most. However, we value the reduction
in total elapsed time the most and we valued how the insertion times were much lower than any other implementation. 
