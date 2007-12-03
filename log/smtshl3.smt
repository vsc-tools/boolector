(benchmark bvshl3
 :logic QF_BV

 :assumption (= (bvshl bv0[3] bv0[3]) bv0[3])
 :assumption (= (bvshl bv0[3] bv1[3]) bv0[3])
 :assumption (= (bvshl bv0[3] bv2[3]) bv0[3])
 :assumption (= (bvshl bv0[3] bv3[3]) bv0[3])
 :assumption (= (bvshl bv0[3] bv4[3]) bv0[3])
 :assumption (= (bvshl bv0[3] bv5[3]) bv0[3])
 :assumption (= (bvshl bv0[3] bv6[3]) bv0[3])
 :assumption (= (bvshl bv0[3] bv7[3]) bv0[3])

 :assumption (= (bvshl bv1[3] bv0[3]) bv1[3])
 :assumption (= (bvshl bv1[3] bv1[3]) bv2[3])
 :assumption (= (bvshl bv1[3] bv2[3]) bv4[3])
 :assumption (= (bvshl bv1[3] bv3[3]) bv0[3])
 :assumption (= (bvshl bv1[3] bv4[3]) bv0[3])
 :assumption (= (bvshl bv1[3] bv5[3]) bv0[3])
 :assumption (= (bvshl bv1[3] bv6[3]) bv0[3])
 :assumption (= (bvshl bv1[3] bv7[3]) bv0[3])

 :assumption (= (bvshl bv2[3] bv0[3]) bv2[3])
 :assumption (= (bvshl bv2[3] bv1[3]) bv4[3])
 :assumption (= (bvshl bv2[3] bv2[3]) bv0[3])
 :assumption (= (bvshl bv2[3] bv3[3]) bv0[3])
 :assumption (= (bvshl bv2[3] bv4[3]) bv0[3])
 :assumption (= (bvshl bv2[3] bv5[3]) bv0[3])
 :assumption (= (bvshl bv2[3] bv6[3]) bv0[3])
 :assumption (= (bvshl bv2[3] bv7[3]) bv0[3])

 :assumption (= (bvshl bv3[3] bv0[3]) bv3[3])
 :assumption (= (bvshl bv3[3] bv1[3]) bv6[3])
 :assumption (= (bvshl bv3[3] bv2[3]) bv4[3])
 :assumption (= (bvshl bv3[3] bv3[3]) bv0[3])
 :assumption (= (bvshl bv3[3] bv4[3]) bv0[3])
 :assumption (= (bvshl bv3[3] bv5[3]) bv0[3])
 :assumption (= (bvshl bv3[3] bv6[3]) bv0[3])
 :assumption (= (bvshl bv3[3] bv7[3]) bv0[3])

 :assumption (= (bvshl bv4[3] bv0[3]) bv4[3])
 :assumption (= (bvshl bv4[3] bv1[3]) bv0[3])
 :assumption (= (bvshl bv4[3] bv2[3]) bv0[3])
 :assumption (= (bvshl bv4[3] bv3[3]) bv0[3])
 :assumption (= (bvshl bv4[3] bv4[3]) bv0[3])
 :assumption (= (bvshl bv4[3] bv5[3]) bv0[3])
 :assumption (= (bvshl bv4[3] bv6[3]) bv0[3])
 :assumption (= (bvshl bv4[3] bv7[3]) bv0[3])

 :assumption (= (bvshl bv5[3] bv0[3]) bv5[3])
 :assumption (= (bvshl bv5[3] bv1[3]) bv2[3])
 :assumption (= (bvshl bv5[3] bv2[3]) bv4[3])
 :assumption (= (bvshl bv5[3] bv3[3]) bv0[3])
 :assumption (= (bvshl bv5[3] bv4[3]) bv0[3])
 :assumption (= (bvshl bv5[3] bv5[3]) bv0[3])
 :assumption (= (bvshl bv5[3] bv6[3]) bv0[3])
 :assumption (= (bvshl bv5[3] bv7[3]) bv0[3])

 :assumption (= (bvshl bv6[3] bv0[3]) bv6[3])
 :assumption (= (bvshl bv6[3] bv1[3]) bv4[3])
 :assumption (= (bvshl bv6[3] bv2[3]) bv0[3])
 :assumption (= (bvshl bv6[3] bv3[3]) bv0[3])
 :assumption (= (bvshl bv6[3] bv4[3]) bv0[3])
 :assumption (= (bvshl bv6[3] bv5[3]) bv0[3])
 :assumption (= (bvshl bv6[3] bv6[3]) bv0[3])
 :assumption (= (bvshl bv6[3] bv7[3]) bv0[3])

 :assumption (= (bvshl bv7[3] bv0[3]) bv7[3])
 :assumption (= (bvshl bv7[3] bv1[3]) bv6[3])
 :assumption (= (bvshl bv7[3] bv2[3]) bv4[3])
 :assumption (= (bvshl bv7[3] bv3[3]) bv0[3])
 :assumption (= (bvshl bv7[3] bv4[3]) bv0[3])
 :assumption (= (bvshl bv7[3] bv5[3]) bv0[3])
 :assumption (= (bvshl bv7[3] bv6[3]) bv0[3])
 :assumption (= (bvshl bv7[3] bv7[3]) bv0[3])

 :formula true)
