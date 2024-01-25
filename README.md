# Vz correction

version 5.0

author: Yige Huang

date: 25.01.2024

## Quick Start

1. `make run1`, make the executable `run1` to get the raw distribution.

2. run it.

3. find straight lines to do the pile up correction, and set them in `src2.cxx`.

4. `make run2`, to get the pile-up-rejected distribution.

5. run it.

6. change `k` and `b` parameters in `plot.cxx` and `root -l -b -q plot.cxx`.

## Change Log

25.01.2024 by yghuang (5.0):

> Support RefMult3X.
>
>> When do fit, one more argument is needed, 3 or 3X.

27.11.2023 by yghuang (4.1):

> New centrality tree / tool.

09.10.2023 by yghuang (4.0):

> Using new version of centrality utils (updated pile-up rejection).

Aug. 7, 2023 by yghuang (3.0):

> Using new centrlaity util package, see [here](https://github.com/LearnerYme/CentralityUtils.git).

Feb. 7, 2023 by yghuang (2.1):

> Add a SubmitUtils in case you have a big data set (like 19.6).
>
> This can help you split the jobs and merge them then.

Feb. 1, 2023 by yghuang (2.0):

> Using centrality util.

