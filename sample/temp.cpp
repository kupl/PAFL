# 평가에서 제외된 프로젝트
{ jerryscript , wireshark } - 현재 구현으로 문법 오류가 있는 매크로 파일을 tokenizing 불가능
{ md4c, yaml_cpp, yara } - 버그 정리가 끝나지 않음


# Eval
Baseline = 13 , PAFL = 20 으로 54%의 성능 향상을 보임


# 초기 학습 단계 5개를 제외한 개별 평가

  < cpp_peglib >
  avg :   0.6748470624922711
  best :  0.25763612217795484
  worst : 1.0
  top_10:  ochiai->pafl = 2 -> 2
  top_50:  ochiai->pafl = 4 -> 4
  top_100: ochiai->pafl = 6 -> 6
  win : 4
  draw : 1
  lose : 0

  < cppcheck >
  avg :   0.7692046057731804
  best :  0.04
  worst : 1.3633923778851316
  top_10:  ochiai->pafl = 0 -> 3
  top_50:  ochiai->pafl = 0 -> 4
  top_100: ochiai->pafl = 5 -> 8
  win : 17
  draw : 5
  lose : 3

  < exiv2 >
  avg :   0.928143922761677
  best :  0.25
  worst : 3.142857142857143
  top_10:  ochiai->pafl = 6 -> 8
  top_50:  ochiai->pafl = 11 -> 11
  top_100: ochiai->pafl = 14 -> 13
  win : 7
  draw : 5
  lose : 3

  < libchewing >
  avg :   0.7296779249054515
  best :  0.5010211027910143
  worst : 0.9323966065747614
  top_10:  ochiai->pafl = 0 -> 0
  top_50:  ochiai->pafl = 0 -> 2
  top_100: ochiai->pafl = 2 -> 2
  win : 3
  draw : 0
  lose : 0

  < libxml2 >
  avg :   0.5848115299334812
  best :  0.18181818181818182
  worst : 0.9878048780487805
  top_10:  ochiai->pafl = 1 -> 2
  top_50:  ochiai->pafl = 4 -> 4
  top_100: ochiai->pafl = 5 -> 5
  win : 1
  draw : 1
  lose : 0

  < openssl >
  avg :   0.8488093006579792
  best :  0.10170304629407531
  worst : 1.6734273490730471
  top_10:  ochiai->pafl = 0 -> 0
  top_50:  ochiai->pafl = 0 -> 0
  top_100: ochiai->pafl = 0 -> 0
  win : 15
  draw : 3
  lose : 3

  < proj >
  avg :   0.8399090080505595
  best :  0.2045602605863192
  worst : 1.4714762155520449
  top_10:  ochiai->pafl = 0 -> 0
  top_50:  ochiai->pafl = 1 -> 1
  top_100: ochiai->pafl = 1 -> 1
  win : 11
  draw : 10
  lose : 2


# 개별 평가

  < coreutils >
  avg :   1.0
  best :  1.0
  worst : 1.0
  top_10:  ochiai->pafl = 1 -> 1
  top_50:  ochiai->pafl = 1 -> 1
  top_100: ochiai->pafl = 1 -> 1
  win : 0
  draw : 2
  lose : 0

  < cpp_peglib >
  avg :   0.8374235312461357
  best :  0.25763612217795484
  worst : 1.0
  top_10:  ochiai->pafl = 2 -> 2
  top_50:  ochiai->pafl = 4 -> 4
  top_100: ochiai->pafl = 6 -> 6
  win : 4
  draw : 6
  lose : 0

  < cppcheck >
  avg :   0.8033836268144284
  best :  0.04
  worst : 1.3633923778851316
  top_10:  ochiai->pafl = 0 -> 3
  top_50:  ochiai->pafl = 0 -> 4
  top_100: ochiai->pafl = 5 -> 8
  win : 18
  draw : 9
  lose : 3

  < dlt_daemon >
  avg :   1.0
  best :  1.0
  worst : 1.0
  top_10:  ochiai->pafl = 0 -> 0
  top_50:  ochiai->pafl = 0 -> 0
  top_100: ochiai->pafl = 1 -> 1
  win : 0
  draw : 1
  lose : 0

  < exiv2 >
  avg :   0.9066342578607316
  best :  0.21052631578947367
  worst : 3.142857142857143
  top_10:  ochiai->pafl = 6 -> 8
  top_50:  ochiai->pafl = 11 -> 11
  top_100: ochiai->pafl = 14 -> 13
  win : 8
  draw : 9
  lose : 3

  < libchewing >
  avg :   0.7079528561155899
  best :  0.14720812182741116
  worst : 1.0
  top_10:  ochiai->pafl = 0 -> 0
  top_50:  ochiai->pafl = 0 -> 2
  top_100: ochiai->pafl = 2 -> 2
  win : 5
  draw : 3
  lose : 0

  < libssh >
  avg :   1.0
  best :  1.0
  worst : 1.0
  top_10:  ochiai->pafl = 0 -> 0
  top_50:  ochiai->pafl = 0 -> 0
  top_100: ochiai->pafl = 0 -> 0
  win : 0
  draw : 1
  lose : 0

  < libtiff >
  avg :   1.0439269738525274
  best :  0.42226487523992323
  worst : 1.7973699940227137
  top_10:  ochiai->pafl = 0 -> 0
  top_50:  ochiai->pafl = 1 -> 1
  top_100: ochiai->pafl = 1 -> 1
  win : 1
  draw : 3
  lose : 1

  < libtiff_sanitizer >
  avg :   1.1885024333474397
  best :  1.0
  worst : 1.3848920863309353
  top_10:  ochiai->pafl = 0 -> 0
  top_50:  ochiai->pafl = 0 -> 0
  top_100: ochiai->pafl = 0 -> 0
  win : 0
  draw : 2
  lose : 2

  < libucl >
  avg :   0.7612359550561798
  best :  0.0449438202247191
  worst : 1.0
  top_10:  ochiai->pafl = 0 -> 1
  top_50:  ochiai->pafl = 0 -> 1
  top_100: ochiai->pafl = 0 -> 1
  win : 1
  draw : 3
  lose : 0

  < libxml2 >
  avg :   0.8174990340454583
  best :  0.18181818181818182
  worst : 1.1587301587301588
  top_10:  ochiai->pafl = 1 -> 2
  top_50:  ochiai->pafl = 4 -> 4
  top_100: ochiai->pafl = 5 -> 5
  win : 2
  draw : 4
  lose : 1

  < ndpi >
  avg :   1.0
  best :  1.0
  worst : 1.0
  top_10:  ochiai->pafl = 2 -> 2
  top_50:  ochiai->pafl = 2 -> 2
  top_100: ochiai->pafl = 3 -> 3
  win : 0
  draw : 4
  lose : 0

  < openssl >
  avg :   0.881576673191258
  best :  0.10170304629407531
  worst : 1.6734273490730471
  top_10:  ochiai->pafl = 0 -> 0
  top_50:  ochiai->pafl = 0 -> 0
  top_100: ochiai->pafl = 0 -> 0
  win : 16
  draw : 6
  lose : 4

  < proj >
  avg :   0.8545944872030604
  best :  0.2045602605863192
  worst : 1.4714762155520449
  top_10:  ochiai->pafl = 0 -> 0
  top_50:  ochiai->pafl = 1 -> 1
  top_100: ochiai->pafl = 1 -> 1
  win : 12
  draw : 14
  lose : 2

  < wget2 >
  avg :   1.0
  best :  1.0
  worst : 1.0
  top_10:  ochiai->pafl = 0 -> 0
  top_50:  ochiai->pafl = 0 -> 0
  top_100: ochiai->pafl = 2 -> 2
  win : 0
  draw : 3
  lose : 0

  < xbps >
  avg :   1.0
  best :  1.0
  worst : 1.0
  top_10:  ochiai->pafl = 1 -> 1
  top_50:  ochiai->pafl = 4 -> 4
  top_100: ochiai->pafl = 4 -> 4
  win : 0
  draw : 5
  lose : 0