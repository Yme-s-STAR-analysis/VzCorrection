# Centrality Correction Utility

author: yghuang

version: 4.0

## Change log

22.11.2023 by yghuang (v4.0):

> Do pile-up correction for separate pile-up quantities.
>
>> Now support vz-dependent pile-up (related to official cuts).

09.10.2023 by yghuang (v3.1):

> New pile-up method, see X2PileUp and X4Vz.
>
> Will load bin edge when read parameters.

10.08.2023 by yghuang (v2.1):

> Important: if we want to include `Conf.h` in multi-code files, parameters there should be static.
>
> Add a centrality bin edge into Conf.h.

07.08.2023 by yghuang (v2.0):

> New version, now use `Conf.h` to contain the correction parameters.
