#include "test.h"
#include <math.h>
#include <stdint.h>
#include <fenv.h>
#include <string.h>
#include <stdio.h>
#include <float.h>

static struct {
	double x, y, z, r;
} testdata[] = {
-0x1p+0, 0x0p0, -0x0p+0, -0x0p+0,
-0x1p+0, 0x1p+0, 0x1p+0, 0x0p+0,
0x1p+0, 0x1p+0, -0x1p+0, 0x0p+0,
-0x1p+0, -0x1p+0, -0x1p+0, 0x0p+0,
0x1.0000000000001p+0, 0x1p+0, 0x1p+53, 0x1.0000000000001p+53,
0x1.0000000000001p+0, 0x1.fffffffffffffp-1, 0x1p+53, 0x1.0000000000001p+53,
0x1p+0, 0x1.fffffffffffffp-1, 0x1.fffffffffffffp+53, 0x1.fffffffffffffp+53,
0x1.0000000000001p+0, 0x1.fffffffffffffp-1, 0x1.ffffffffffffep+53, 0x1.fffffffffffffp+53,
0x1.0000000000001p+0, 0x1.fffffffffffffp-1, 0x1p-52, 0x1.0000000000001p+0,
0x1.0000000000001p+0, 0x1.fffffffffffffp-1, 0x1.fffffffffffffp-53, 0x1.0000000000001p+0,
0x1.0000000000005p+0, 0x1.ffffffffffffbp-1, 0x1p-52, 0x1.0000000000003p+0,
0x1.0000000000006p+0, 0x1.ffffffffffffdp-1, 0x1p-52, 0x1.0000000000005p+0,
0x1.0000000000001p+0, 0x1.fffffffffffffp-1, -0x1p+0, 0x1.ffffffffffffep-54,
0x1.0000000000001p+0, 0x1.fffffffffffffp-1, -0x1.fffffffffffffp-1, 0x1.fffffffffffffp-53,
0x1.0000000000001p+0, 0x1.ffffffffffffep-1, -0x1p+0, -0x1p-104,
0x1.0000000000001p+0, 0x1.ffffffffffffep-1, -0x1.fffffffffffffp-1, 0x1.ffffffffffffcp-54,
0x1.0000000000001p+0, 0x1.ffffffffffffdp-1, -0x1p+0, -0x1.0000000000003p-53,
0x1.0000000000001p+0, 0x1.ffffffffffffdp-1, -0x1.fffffffffffffp-1, -0x1.8p-104,
0x1.0000000000001p+0, 0x1.ffffffffffffdp-1, -0x1.ffffffffffffep-1, 0x1.ffffffffffffap-54,
0x1.0000000000001p+0, 0x1.ffffffffffffcp-1, -0x1p+0, -0x1.0000000000002p-52,
0x1.0000000000001p+0, 0x1.ffffffffffffcp-1, -0x1.fffffffffffffp-1, -0x1.0000000000004p-53,
0x1.0000000000001p+0, 0x1.ffffffffffffcp-1, -0x1.ffffffffffffep-1, -0x1p-103,
0x1.0000000000001p+0, 0x1.ffffffffffffcp-1, -0x1.ffffffffffffdp-1, 0x1.ffffffffffff8p-54,
0x1.fffffffffffffp-1, 0x1.fffffffffffffp-1, -0x1.fffffffffffffp-1, -0x1.fffffffffffffp-54,
0x1.fffffffffffffp-1, 0x1.fffffffffffffp-1, -0x1.ffffffffffffep-1, 0x1p-106,
0x1.fffffffffffffp-1, 0x1.ffffffffffffep-1, -0x1.fffffffffffffp-1, -0x1.fffffffffffffp-53,
0x1.fffffffffffffp-1, 0x1.ffffffffffffep-1, -0x1.ffffffffffffep-1, -0x1.ffffffffffffep-54,
0x1.fffffffffffffp-1, 0x1.ffffffffffffep-1, -0x1.ffffffffffffdp-1, 0x1p-105,
0x1.fffffffffffffp-1, 0x1.ffffffffffffep-1, -0x1.ffffffffffffcp-1, 0x1.0000000000001p-53,
0x1.fffffffffffffp-1, 0x1.ffffffffffffdp-1, -0x1p+0, -0x1.fffffffffffffp-52,
0x1.ffffffffffff7p-1, 0x1.ffffffffffffbp-1, 0x1.ffffffffffff7p-1, 0x1.ffffffffffff5p+0,
0x1.ffffffffffff7p-1, 0x1.ffffffffffffap-1, 0x1p+0, 0x1.ffffffffffff9p+0,
0x1.ffffffffffff7p-1, 0x1.ffffffffffffap-1, 0x1.ffffffffffffcp-1, 0x1.ffffffffffff7p+0,
0x1.ffffffffffff7p-1, 0x1.ffffffffffffap-1, 0x1.ffffffffffff8p-1, 0x1.ffffffffffff5p+0,
0x1.ffffffffffff7p-1, 0x1.ffffffffffff9p-1, 0x1.ffffffffffffdp-1, 0x1.ffffffffffff7p+0,
0x1.ffffffffffff7p-1, 0x1.ffffffffffff9p-1, 0x1.ffffffffffff9p-1, 0x1.ffffffffffff5p+0,
0x1.ffffffffffff7p-1, 0x1.ffffffffffff8p-1, 0x1.ffffffffffffep-1, 0x1.ffffffffffff7p+0,
0x1.ffffffffffff7p-1, 0x1.ffffffffffff8p-1, 0x1.ffffffffffffap-1, 0x1.ffffffffffff5p+0,
0x1.ffffffffffff7p-1, 0x1.ffffffffffff7p-1, 0x1.fffffffffffffp-1, 0x1.ffffffffffff7p+0,
0x1.ffffffffffff7p-1, 0x1.ffffffffffff7p-1, 0x1.ffffffffffffbp-1, 0x1.ffffffffffff5p+0,
0x1.ffffffffffff7p-1, 0x1.ffffffffffff7p-1, 0x1.ffffffffffff7p-1, 0x1.ffffffffffff3p+0,
0x1.0000000000001p+0, 0x1.fffffffffffffp-1, 0x1.ffffffffffffep-1, 0x1.fffffffffffffp+0,
0x1.0000000000001p+0, 0x1.fffffffffffffp-1, 0x1.ffffffffffffap-1, 0x1.ffffffffffffdp+0,
0x1.0000000000001p+0, 0x1.ffffffffffffep-1, 0x1.fffffffffffffp-1, 0x1.fffffffffffffp+0,
0x1.0000000000001p+0, 0x1.ffffffffffffep-1, 0x1.ffffffffffffbp-1, 0x1.ffffffffffffdp+0,
0x1.0000000000001p+0, 0x1.ffffffffffffep-1, 0x1.ffffffffffff7p-1, 0x1.ffffffffffffbp+0,
0x1.0000000000001p+0, 0x1.ffffffffffffdp-1, 0x1p+0, 0x1.fffffffffffffp+0,
0x1.0000000000001p+0, 0x1.ffffffffffffdp-1, 0x1.ffffffffffffcp-1, 0x1.ffffffffffffdp+0,
0x1.0000000000001p+0, 0x1.ffffffffffffdp-1, 0x1.ffffffffffff8p-1, 0x1.ffffffffffffbp+0,
0x1.0000000000001p+0, 0x1.ffffffffffffcp-1, 0x1.ffffffffffffdp-1, 0x1.ffffffffffffdp+0,
0x1.0000000000001p+0, 0x1.ffffffffffffcp-1, 0x1.ffffffffffff9p-1, 0x1.ffffffffffffbp+0,
0x1.0000000000001p+0, 0x1.ffffffffffffbp-1, 0x1.ffffffffffffep-1, 0x1.ffffffffffffdp+0,
0x1.0000000000001p+0, 0x1.ffffffffffffbp-1, 0x1.ffffffffffffap-1, 0x1.ffffffffffffbp+0,
0x1.5872449b765b9p+0, 0x1.c9acf91f8de2bp+0, 0x1.9265607e4d168p+0, 0x1.fd190c77c2a67p+1,
0x1.81d010b146d0ep+0, 0x1.2d3c680dc9071p+0, 0x1.a80b69538754cp+0, 0x1.b7040b44973a7p+1,
0x1.6a44f2252b6a2p+0, 0x1.da452a378b832p+0, 0x1.1fe2ce329104p+0, 0x1.df842b6f48b13p+1,
0x1.096b1d26463eep+0, 0x1.d846d3e34333p+0, 0x1.721e3480922b8p+0, 0x1.ade2909c0269fp+1,
0x1.99bd3434c454bp+0, 0x1.03cb8e4115bdep+0, 0x1.109f107188b08p+0, 0x1.5837a47d37fafp+1,
0x1.ba930a0a78ed2p+0, 0x1.8c24e8d67f636p+0, 0x1.ac49dbfbf8affp+0, 0x1.164947ae6a5d9p+2,
0x1.be224ad773191p+0, 0x1.d96b77169731fp+0, 0x1.662cfb75d8edep+0, 0x1.27cd67e720f79p+2,
0x1.59e7a1b0bdb3cp+0, 0x1.2decba4d46421p+0, 0x1.88f4062e96df5p+0, 0x1.90749e4794f79p+1,
0x1.22edf4b4da9a7p+0, 0x1.dfa8d65f506cdp+0, 0x1.2799208da2fbap+0, 0x1.a45a1e99ed7a9p+1,
0x1.ad5b991a2a279p+0, 0x1.f02fd26706024p+0, 0x1.831cdd5c8797cp+0, 0x1.30d3a2ac90a61p+2,
0x1.531f9620e764ap+0, 0x1.cad61b54d4425p+0, 0x1.df817cae8a9afp+0, 0x1.0fd4e7f8671ddp+2,
0x1.629a5ad79494fp+0, 0x1.049e58693f4c4p+0, 0x1.45b0109e4d00cp+0, 0x1.5758154e14965p+1,
0x1.2f52b53f9240ap+0, 0x1.1d5c686dbb0dap+0, 0x1.6da3e392a4fd4p+0, 0x1.5fe03a6795913p+1,
0x1.058667552b49ep+0, 0x1.23307bacc1c42p+0, 0x1.5b059b47cd8f5p+0, 0x1.423f752486d13p+1,
0x1.a717d95337ed8p+0, 0x1.2b1c37846aaadp+0, 0x1.be65672f885b1p+0, 0x1.d65e72303c075p+1,
0x1.deb79287b3d32p+0, 0x1.62776b829babap+0, 0x1.67daf18bd2eb1p+0, 0x1.ff5a0d45c69d7p+1,
0x1.fbf12d3a6de91p+0, 0x1.879fe6124f11p+0, 0x1.9f3f1247a8641p+0, 0x1.2a126c6980019p+2,
0x1.c589628460e01p+0, 0x1.e1bec1c797533p+0, 0x1.349f30cdb84bbp+0, 0x1.2286118b6f6e5p+2,
0x1.46fd6c2c924ebp+0, 0x1.65e2f02e730a1p+0, 0x1.37739d2751098p+0, 0x1.804a71c1f1273p+1,
0x1.f99e595ae11fdp+0, 0x1.bd33d9a1d81bp+0, 0x1.932a2a2e244c1p+0, 0x1.409e34f8f2f89p+2,
0x1.59ea1e56bfe55p+0, 0x1.6f46b7d412a44p+0, 0x1.80f2bc9a32cc3p+0, 0x1.b89c7640e32ffp+1,
0x1.61490fcb44129p+0, 0x1.0038ec4fc35c2p+0, 0x1.df7436ed7a7b7p+0, 0x1.a085ea68d05cfp+1,
0x1.d41b98788502bp+0, 0x1.1a7b77843aca6p+0, 0x1.05be891837d36p+0, 0x1.8523596ceced9p+1,
0x1.3153cf6f69af9p+0, 0x1.aaa947e38e57ap+0, 0x1.8519f9b590645p+0, 0x1.c0fcab7b46369p+1,
0x1.c25a1f73581aap+0, 0x1.0a51ffca372ap+0, 0x1.0c77e3ebac5f3p+0, 0x1.707ce48c7d72dp+1,
0x1.829c2cde44b7p+0, 0x1.f692e86d8cb36p+0, 0x1.455e72d264bfp+0, 0x1.0f16a3b8b3f97p+2,
0x1.94729588dcc69p+0, 0x1.c3bb794c6edf8p+0, 0x1.9da4e94d262d2p+0, 0x1.19d4bd84d9fd3p+2,
0x1.e6a5e7e39c3d5p+0, 0x1.1b69af2bdd978p+0, 0x1.e7ef1eafa119cp+0, 0x1.00ac5b44c9f31p+2,
0x1.bc9ba1320700cp-1022, 0x1.981f2e1a451a8p-2, 0x1.046144efc0ceap-1022, 0x1.b594d0e4368efp-1022,
0x1.022db53c98d14p-1022, 0x1.21157eef74848p-2, 0x1.2f880432b1bc1p-1022, 0x1.786ad60a02b3dp-1022,
0x1.805a491fa9597p-1022, 0x1.e0f49d782ff87p-2, 0x1.172a62346206p-1022, 0x1.cbb085199a3f5p-1022,
0x1.adbc3a9d816dep-1022, 0x1.e039d4431e3cdp-2, 0x1.93ceef6fe18a2p-1022, 0x1.2eabb7dc0e2f1p-1021,
0x1.645aa5c2df3afp-1022, 0x1.649edfcad854fp-2, 0x1.8b43e0bbaeb01p-1022, 0x1.03af571d2b505p-1021,
0x1.133474a2c0fb1p-1022, 0x1.72442bcbfa01dp-2, 0x1.4a1a21971c5dbp-1022, 0x1.ad9ce7fcefa3fp-1022,
0x1.8ee3feb00c3e7p-1022, 0x1.53bd9353313bcp-2, 0x1.5501b57dc3b6fp-1022, 0x1.d9598906f0bb3p-1022,
0x1.161225cfa61e2p-1022, 0x1.b6dd69a0af5bp-2, 0x1.924ffc3ead5c3p-1022, 0x1.04be6fc25367bp-1021,
0x1.820f7faf219afp-1022, 0x1.06717ae771f6dp-2, 0x1.0dc5035f5e2afp-1022, 0x1.70b6c3169f043p-1022,
0x1.ce0e2ea55040ep-1022, 0x1.ce5a55fa3828dp-2, 0x1.f2f444d50ce59p-1022, 0x1.61ca36f5a8a79p-1021,
0x1.a7a271c67cdcfp-1022, 0x1.1e979090e218p-2, 0x1.b1f10b6e2177ap-1022, 0x1.1440cf1c105ebp-1021,
0x1.76df065829dc6p-1022, 0x1.fb22ab1b86b8bp-2, 0x1.6966267f317cp-1022, 0x1.1186e1f77012dp-1021,
0x1.8b004a28b70dbp-1022, 0x1.48e5805a8b453p-2, 0x1.0ea791f716557p-1022, 0x1.8d86310bad175p-1022,
0x1.fb3391a4b1d23p-1022, 0x1.4d8705b057caep-2, 0x1.d026cb6dae73bp-1022, 0x1.3aad18b424c67p-1021,
0x1.a5ba39730e197p-1022, 0x1.794df89b1cc49p-2, 0x1.24a0a388d0b6bp-1022, 0x1.c0048fd33a417p-1022,
0x1.aa9eff070281cp-1022, 0x1.fab05661b48ebp-2, 0x1.cbe2af6c69c6ep-1022, 0x1.4f7ddbe122765p-1021,
0x1.758bbff0ec4bap-1022, 0x1.a4a197f3fa424p-2, 0x1.47761e8d142ddp-1022, 0x1.e0e762ee2e7c5p-1022,
0x1.4dab43918a9a8p-1022, 0x1.ed667442b4751p-2, 0x1.3f25f82e02e3ep-1022, 0x1.dfec0ee732dcbp-1022,
0x1.7943735951931p-1022, 0x1.fa6a357c5c9ddp-2, 0x1.0bed44b0b71b4p-1022, 0x1.c6803a6059abfp-1022,
0x1.66c26bc29a5e8p-1022, 0x1.3faed079f761ap-2, 0x1.163ff906dd651p-1022, 0x1.8640492c45959p-1022,
0x1.f52172c56bdf5p-1022, 0x1.672b2de422734p-2, 0x1.7bc5d708e5a34p-1022, 0x1.15c5b95145cc7p-1021,
0x1.2f94e89aa7558p-1022, 0x1.dfa6d30835f5ep-2, 0x1.59c6b0d504cf9p-1022, 0x1.e7fa0dd76fbefp-1022,
0x1.6159897ae533cp-1022, 0x1.f3b8892e3a3c8p-2, 0x1.09ca702b7759p-1022, 0x1.b63a7f56fce1fp-1022,
0x1.f73d5f4e81fd8p-1022, 0x1.7ccff2642124ap-2, 0x1.e7d836a0c8308p-1022, 0x1.517f1763126d3p-1021,
0x1.b4328925969fbp-1022, 0x1.8fa02832a22d5p-2, 0x1.2084598e2f8c6p-1022, 0x1.cabf43838dc51p-1022,
0x1.66ee60a92676fp-1022, 0x1.eddd2e7681ce4p-2, 0x1.b81d57daeb3a7p-1022, 0x1.329c918ffb683p-1021,
0x1.ff2737585895dp-1022, 0x1.fb4bf3828ae4ap-2, 0x1.4a866847740fp-1022, 0x1.23e07e4dbbeabp-1021,
0x1.5e2008d269a86p-1022, 0x1.507bbbe4d78eep-2, 0x1.6220c6f83f636p-1022, 0x1.d52d9874f1c75p-1022,
0x1.ce7e2e5812d86p-1022, 0x1.0e6689d092e5fp-2, 0x1.1e43fd55c3458p-1022, 0x1.9864925e2fb0fp-1022,
0x1.7b353b81e793dp-1022, 0x1.82b426f874c6dp-2, 0x1.d92b19d21fd5cp-1022, 0x1.342fb0c544a79p-1021,
0x1.5be667823370ap-1022, 0x1.a8a99b163869bp-2, 0x1.95456b68dc3bcp-1022, 0x1.12c638de03c71p-1021,
0x1.17b0fc6c850e5p-1022, 0x1.d1d0a4853c315p-2, 0x1.36b79f7c0c24p-1022, 0x1.b5f2baff5635dp-1022,
0x1.bd97819bacfd8p-1022, 0x1.2c25f267ba4eep-2, 0x1.804b5204a3f3ap-1022, 0x1.01739c190fd97p-1021,
0x1.596577053873dp-1022, 0x1.3562ab2d29949p-2, 0x1.b3f1ee75db6e7p-1022, 0x1.0e268a498009bp-1021,
0x1.3c7a68cf0f7b3p-1022, 0x1.9a55c15b167bdp-2, 0x1.7635b7b163c07p-1022, 0x1.f5073b93b7b81p-1022,
0x1.5825164bc4068p-1022, 0x1.dcbb6e5ff3245p-2, 0x1.52fc3be0e84dap-1022, 0x1.f334771c2dcfbp-1022,
0x1.139ea77b760ecp+1022, 0x1.9b25f2fd017eap+2, -0x1.bc16788922b6fp+1023, 0x1.b93aac527380fp+1023,
0x1.0e6f9c1657d7cp+1022, 0x1.4d5c6b55ab5f1p+2, -0x1.e027dd5742e2cp+1023, 0x1.c0538372b4bbfp+1022,
0x1.1182524fa411cp+1022, 0x1.a3dba56842d19p+2, -0x1.c1ad59474d71fp+1023, 0x1.bf78969300a77p+1023,
0x1.1cbf4fb8ec82p+1022, 0x1.5e32019a84fbbp+2, -0x1.985af08f32edep+1023, 0x1.72af6bbad4a29p+1023,
0x1.311e25c6db346p+1022, 0x1.4e30db6c4b51dp+2, -0x1.7681f7a9786a7p+1023, 0x1.a61d29434fc13p+1023,
0x1.1201cf577052fp+1022, 0x1.59730b2db7a16p+2, -0x1.56f1a64a078d5p+1023, 0x1.8c8d801df34d9p+1023,
0x1.3e52335b76e81p+1022, 0x1.4dbd56f857479p+2, -0x1.509340c11bd2ep+1023, 0x1.ed6576837f653p+1023,
0x1.18566b4f843cbp+1022, 0x1.444fba10eaf29p+2, -0x1.f927beae57f0ap+1023, 0x1.9a433b9796559p+1022,
0x1.3fbe544fe1be8p+1022, 0x1.2d2a5fda03639p+2, -0x1.007407dbfd03cp+1023, 0x1.efdb644b613e5p+1023,
0x1.263a0d3bc2e4p+1022, 0x1.4cc198adbc651p+2, -0x1.734b1c1f7fdb8p+1023, 0x1.899878afc0fa3p+1023,
0x1.5bf4aec8efc8ep+1022, 0x1.555f0341516c9p+2, -0x1.c706408acd14cp+1023, 0x1.d8f5e18b868bdp+1023,
0x1.1e57f1af78279p+1022, 0x1.34bc0c7f082b3p+2, -0x1.497b92c1365edp+1023, 0x1.692cb7ec68a93p+1023,
0x1.1d9824cd73511p+1022, 0x1.1d557ddfe47ffp+2, -0x1.556cdb1d20a72p+1023, 0x1.2736a6b6e35f3p+1023,
0x1.1ff85a24aff31p+1022, 0x1.39ab374b2680dp+2, -0x1.35e6b07b651b8p+1023, 0x1.8bc7ce2087081p+1023,
0x1.0449b3965227ep+1022, 0x1.4430d4441f9f2p+2, -0x1.a6966c96307ep+1023, 0x1.d94eda8c81771p+1022,
0x1.3c91fa00fd0c7p+1022, 0x1.1b6661c0b0303p+2, -0x1.f1f2846b64483p+1023, 0x1.95eae0d2644d3p+1022,
0x1.0979b36d46534p+1022, 0x1.12fa205f41f7fp+2, -0x1.a83ecf4544a63p+1023, 0x1.2420f34e2aa3dp+1022,
0x1.4c89df582a599p+1022, 0x1.55f3dc473ea8fp+2, -0x1.e35037292ddfp+1023, 0x1.95109fdbc3771p+1023,
0x1.35ee0a669c4fbp+1022, 0x1.2263cb63f386ap+2, -0x1.449218ae35ac7p+1023, 0x1.7a8ed977d817bp+1023,
0x1.117cc860f61bcp+1022, 0x1.440985b25d994p+2, -0x1.d7a7d82000449p+1023, 0x1.b960b7088e74fp+1022,
0x1.1e78a37be320fp+1022, 0x1.0db0fce62287bp+2, -0x1.376337da5eb53p+1023, 0x1.24326b9956dfbp+1023,
0x1.0c79b5c8331c2p+1022, 0x1.0aba6ea746b5p+2, -0x1.c86f1fcaf0741p+1023, 0x1.9c135bb2cff85p+1021,
0x1.556c4c072f272p+1022, 0x1.347758d7d4eb5p+2, -0x1.c6fe4f24b248dp+1023, 0x1.6fcc9f756df6dp+1023,
-0x1.e8349b891b2fp-1, 0x1.4a6dec9b72578p-1, 0x1.3b6151ce809ddp-1, 0x1.3a62fe330b355p-11,
0x1.2996632ac7d74p-1, -0x1.bb3c58b654d94p-1, 0x1.01a6660e64a31p-1, 0x1.ed045bb956a8ep-15,
-0x1.c602e894c1df8p-1, 0x1.a1c980e7d3f94p-1, 0x1.7271244b43386p-1, -0x1.ba251fe026e5bp-15,
-0x1.c84baf47e85cp-1, 0x1.770b5149ef2ep-1, 0x1.4d80f139320bap-1, -0x1.79277433b9e23p-10,
-0x1.36e667dcf9c6p-1, 0x1.2591f82556b88p-1, 0x1.2452a0f795f95p-1, 0x1.c83c8e63c159fp-3,
0x1.88b2cede61e4cp-1, -0x1.71dcab5ad9e9p-3, 0x1.32b27fea2ae97p-3, 0x1.70461909b25e2p-7,
0x1.8d1e44002c98p-3, -0x1.af9fdfb347834p-1, 0x1.e280942fb4146p-4, -0x1.761ac23896dfdp-5,
0x1.236e8cb9492c8p-1, -0x1.d37443a57f1c4p-1, 0x1.ca10df801aabcp-4, -0x1.a1a2cdf0138f9p-2,
-0x1.6ad943e610fb8p-1, -0x1.cef92a7bb18bcp-1, 0x1.f28587d8fb0ep-4, 0x1.866b5204b9aecp-1,
-0x1.60a8569a5d894p-1, -0x1.ca07e29dd171cp-1, 0x1.b6c475ace09ecp-4, 0x1.72549291e2f7ap-1,
0x1.d1962720d678cp-1, -0x1.4548ee45c4084p-1, 0x1.f416ab193d75cp-4, -0x1.d2929879dc853p-2,
-0x1.9ddcb295a7d64p-1, 0x1.67fb3a2068a78p-1, 0x1.da9cd4597fe0ap-4, -0x1.cf4f6eb4fc5d8p-2,
0x1.c00d16ed45b88p+0, 0x1.c787eddda3664p+0, 0x1.1e3e6f0cc1802p-5, 0x1.931b8f379dcc3p+1,
0x1.19c2a2372c184p+0, -0x1.cb506961c19fp+0, 0x1.db1abf3f7ba3ap-6, -0x1.f21c0eab0bc18p+0,
-0x1.3a263218ccd1cp+0, -0x1.e818d390df27cp+0, 0x1.2a81ed71785f5p-5, 0x1.3025ab0f63925p+1,
0x1.b0b041fbaca58p+0, -0x1.9d5f76d178e6p+0, 0x1.0215c7bb84cf9p-6, -0x1.5b52aec7ef4p+1,
-0x1.377549d9a87f4p+0, -0x1.a13d4a03dd6d8p+0, 0x1.f190388bc5cc6p-7, 0x1.ff83bebbd6fe4p+0,
0x1.6a726c0762ac8p-1, -0x1.d32f2d30e483cp+0, 0x1.f953eb70fbde6p-7, -0x1.46c61b3070332p+0,
0x1.94cf2509d40cp-1, 0x1.721976af6dfbp+0, 0x1.f51a456921c3ep-7, 0x1.28880842acc6p+0,
0x1.b128eb0ad8728p-1, 0x1.7682566a54268p+0, 0x1.bd4122a074cafp-8, 0x1.3e9469530e762p+0,
0x1.c4ae75976e35cp+0, -0x1.11c329dd1160cp+0, 0x1.9993f5e13c9bdp-8, -0x1.e27d925b07cf1p+0,
-0x1.85f81f88fa3c4p+0, -0x1.17648a494fa18p-1, 0x1.37d305113b48p-10, 0x1.aa367b7490e57p-1,
-0x1.311f2b4319efcp+0, 0x1.abbb5272e3d18p-1, 0x1.35841b7bdbcfep-10, -0x1.fd337f24b39ep-1,
0x1.ab94369a9a0dp-1, 0x1.9d1e0e0aa3bacp+0, 0x1.0a63ca87cfa78p-11, 0x1.592173ee296b6p+0,
};

void bench_fma(int N)
{
	int i;
	double x, y, z;
	volatile double r;

	x = 0x1.629a5ad79494fp+0;
	y = 0x1.049e58693f4c4p+0;
	z = 0x1.45b0109e4d00cp+0;
	for (i = 0; i < N; i++) {
		r = fma(x, y, z);
		x += 0.00001;
	}
}

void test_fma()
{
	int j, c;
	double x, y, z, r, r0;

	c = 0;
	for (j = 0; j < sizeof testdata / sizeof *testdata; j++) {
		x = testdata[j].x;
		y = testdata[j].y;
		z = testdata[j].z;
		r0 = testdata[j].r;
		r = fma(x, y, z);
		if (r != r0 || signbit(r) != signbit(r0)) {
			c++;
			error("fma(%a,%a,%a): wanted %a got %a\n", x, y, z, r0, r);
		}
	}
	if (c)
		printf("errors: %d\n", c);
}
