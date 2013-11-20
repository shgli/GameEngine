#include <cmath>
#include "Math/Algorithm.h"
#include "Math/MathException.h"

static const int32_t SIN_COS_INTERVAL_COUNT = 512;
static const int32_t SIN_COS_ITEM_COUNT = SIN_COS_INTERVAL_COUNT + 1;
static const double TABLE_INTERVAL = PI_DIV_2 / SIN_COS_INTERVAL_COUNT;
double SIN_COS_TABLE[SIN_COS_ITEM_COUNT][2] = 
{{0.000000000000,1.000000000000},{0.003067956763,0.999995293810},{0.006135884649,0.999981175283},{0.009203754782,0.999957644552}
,{0.012271538286,0.999924701839},{0.015339206285,0.999882347454},{0.018406729906,0.999830581796},{0.021474080275,0.999769405351}
,{0.024541228523,0.999698818696},{0.027608145779,0.999618822495},{0.030674803177,0.999529417501},{0.033741171851,0.999430604555}
,{0.036807222941,0.999322384588},{0.039872927588,0.999204758618},{0.042938256935,0.999077727753},{0.046003182131,0.998941293187}
,{0.049067674327,0.998795456205},{0.052131704680,0.998640218180},{0.055195244350,0.998475580573},{0.058258264500,0.998301544934}
,{0.061320736302,0.998118112900},{0.064382630930,0.997925286199},{0.067443919564,0.997723066644},{0.070504573390,0.997511456140}
,{0.073564563600,0.997290456679},{0.076623861392,0.997060070339},{0.079682437971,0.996820299291},{0.082740264549,0.996571145791}
,{0.085797312344,0.996312612183},{0.088853552583,0.996044700901},{0.091908956497,0.995767414468},{0.094963495330,0.995480755492}
,{0.098017140330,0.995184726672},{0.101069862755,0.994879330795},{0.104121633872,0.994564570734},{0.107172424957,0.994240449453}
,{0.110222207294,0.993906970002},{0.113270952178,0.993564135521},{0.116318630912,0.993211949235},{0.119365214811,0.992850414460}
,{0.122410675199,0.992479534599},{0.125454983412,0.992099313142},{0.128498110794,0.991709753669},{0.131540028703,0.991310859846}
,{0.134580708507,0.990902635428},{0.137620121586,0.990485084256},{0.140658239333,0.990058210262},{0.143695033150,0.989622017463}
,{0.146730474455,0.989176509965},{0.149764534677,0.988721691960},{0.152797185258,0.988257567731},{0.155828397654,0.987784141645}
,{0.158858143334,0.987301418158},{0.161886393780,0.986809401814},{0.164913120490,0.986308097245},{0.167938294975,0.985797509168}
,{0.170961888760,0.985277642389},{0.173983873387,0.984748501802},{0.177004220412,0.984210092387},{0.180022901406,0.983662419212}
,{0.183039887955,0.983105487431},{0.186055151663,0.982539302287},{0.189068664150,0.981963869110},{0.192080397050,0.981379193314}
,{0.195090322016,0.980785280403},{0.198098410718,0.980182135968},{0.201104634842,0.979569765685},{0.204108966093,0.978948175319}
,{0.207111376192,0.978317370720},{0.210111836880,0.977677357825},{0.213110319916,0.977028142658},{0.216106797076,0.976369731330}
,{0.219101240157,0.975702130039},{0.222093620973,0.975025345067},{0.225083911360,0.974339382786},{0.228072083171,0.973644249651}
,{0.231058108281,0.972939952206},{0.234041958584,0.972226497079},{0.237023605994,0.971503890986},{0.240003022449,0.970772140729}
,{0.242980179903,0.970031253195},{0.245955050336,0.969281235357},{0.248927605746,0.968522094274},{0.251897818154,0.967753837093}
,{0.254865659605,0.966976471045},{0.257831102162,0.966190003445},{0.260794117915,0.965394441698},{0.263754678975,0.964589793290}
,{0.266712757475,0.963776065795},{0.269668325573,0.962953266874},{0.272621355450,0.962121404269},{0.275571819311,0.961280485811}
,{0.278519689385,0.960430519416},{0.281464937926,0.959571513082},{0.284407537211,0.958703474896},{0.287347459545,0.957826413028}
,{0.290284677254,0.956940335732},{0.293219162694,0.956045251350},{0.296150888244,0.955141168306},{0.299079826308,0.954228095109}
,{0.302005949319,0.953306040354},{0.304929229735,0.952375012720},{0.307849640042,0.951435020969},{0.310767152750,0.950486073949}
,{0.313681740399,0.949528180593},{0.316593375556,0.948561349916},{0.319502030816,0.947585591018},{0.322407678801,0.946600913083}
,{0.325310292162,0.945607325381},{0.328209843579,0.944604837261},{0.331106305760,0.943593458162},{0.333999651442,0.942573197601}
,{0.336889853392,0.941544065183},{0.339776884407,0.940506070593},{0.342660717312,0.939459223602},{0.345541324964,0.938403534063}
,{0.348418680249,0.937339011913},{0.351292756086,0.936265667170},{0.354163525420,0.935183509939},{0.357030961233,0.934092550404}
,{0.359895036535,0.932992798835},{0.362755724367,0.931884265582},{0.365612997805,0.930766961079},{0.368466829953,0.929640895843}
,{0.371317193952,0.928506080473},{0.374164062971,0.927362525650},{0.377007410216,0.926210242138},{0.379847208924,0.925049240783}
,{0.382683432365,0.923879532511},{0.385516053844,0.922701128334},{0.388345046699,0.921514039342},{0.391170384302,0.920318276709}
,{0.393992040061,0.919113851690},{0.396809987417,0.917900775621},{0.399624199846,0.916679059921},{0.402434650859,0.915448716088}
,{0.405241314005,0.914209755704},{0.408044162865,0.912962190428},{0.410843171058,0.911706032005},{0.413638312238,0.910441292258}
,{0.416429560098,0.909167983091},{0.419216888363,0.907886116488},{0.422000270800,0.906595704515},{0.424779681209,0.905296759318}
,{0.427555093430,0.903989293123},{0.430326481340,0.902673318237},{0.433093818853,0.901348847046},{0.435857079922,0.900015892016}
,{0.438616238539,0.898674465694},{0.441371268732,0.897324580705},{0.444122144570,0.895966249756},{0.446868840162,0.894599485631}
,{0.449611329655,0.893224301196},{0.452349587234,0.891840709392},{0.455083587126,0.890448723245},{0.457813303599,0.889048355855}
,{0.460538710958,0.887639620403},{0.463259783552,0.886222530149},{0.465976495768,0.884797098431},{0.468688822036,0.883363338666}
,{0.471396736826,0.881921264348},{0.474100214651,0.880470889052},{0.476799230063,0.879012226429},{0.479493757660,0.877545290207}
,{0.482183772079,0.876070094195},{0.484869248001,0.874586652278},{0.487550160148,0.873094978418},{0.490226483288,0.871595086656}
,{0.492898192230,0.870086991109},{0.495565261826,0.868570705971},{0.498227666973,0.867046245516},{0.500885382611,0.865513624091}
,{0.503538383726,0.863972856122},{0.506186645345,0.862423956111},{0.508830142543,0.860866938638},{0.511468850438,0.859301818357}
,{0.514102744193,0.857728610000},{0.516731799018,0.856147328375},{0.519355990166,0.854557988365},{0.521975292937,0.852960604930}
,{0.524589682678,0.851355193105},{0.527199134782,0.849741768001},{0.529803624686,0.848120344803},{0.532403127877,0.846490938774}
,{0.534997619887,0.844853565250},{0.537587076296,0.843208239642},{0.540171472730,0.841554977437},{0.542750784865,0.839893794196}
,{0.545324988422,0.838224705555},{0.547894059173,0.836547727224},{0.550457972937,0.834862874986},{0.553016705580,0.833170164702}
,{0.555570233020,0.831469612303},{0.558118531221,0.829761233795},{0.560661576197,0.828045045258},{0.563199344014,0.826321062846}
,{0.565731810784,0.824589302785},{0.568258952670,0.822849781376},{0.570780745887,0.821102514991},{0.573297166698,0.819347520077}
,{0.575808191418,0.817584813152},{0.578313796412,0.815814410807},{0.580813958096,0.814036329706},{0.583308652938,0.812250586585}
,{0.585797857456,0.810457198253},{0.588281548223,0.808656181588},{0.590759701859,0.806847553544},{0.593232295040,0.805031331143}
,{0.595699304492,0.803207531481},{0.598160706996,0.801376171723},{0.600616479384,0.799537269108},{0.603066598540,0.797690840943}
,{0.605511041404,0.795836904609},{0.607949784968,0.793975477554},{0.610382806276,0.792106577300},{0.612810082429,0.790230221437}
,{0.615231590581,0.788346427627},{0.617647307938,0.786455213599},{0.620057211763,0.784556597156},{0.622461279374,0.782650596167}
,{0.624859488142,0.780737228572},{0.627251815495,0.778816512381},{0.629638238915,0.776888465673},{0.632018735940,0.774953106595}
,{0.634393284164,0.773010453363},{0.636761861236,0.771060524262},{0.639124444864,0.769103337646},{0.641481012809,0.767138911936}
,{0.643831542890,0.765167265622},{0.646176012983,0.763188417263},{0.648514401022,0.761202385484},{0.650846684996,0.759209188978}
,{0.653172842954,0.757208846506},{0.655492853000,0.755201376897},{0.657806693297,0.753186799044},{0.660114342067,0.751165131910}
,{0.662415777590,0.749136394523},{0.664710978203,0.747100605980},{0.666999922304,0.745057785441},{0.669282588347,0.743007952135}
,{0.671558954847,0.740951125355},{0.673829000379,0.738887324461},{0.676092703575,0.736816568877},{0.678350043130,0.734738878096}
,{0.680600997795,0.732654271672},{0.682845546385,0.730562769228},{0.685083667773,0.728464390448},{0.687315340892,0.726359155084}
,{0.689540544737,0.724247082951},{0.691759258364,0.722128193929},{0.693971460890,0.720002507961},{0.696177131491,0.717870045056}
,{0.698376249409,0.715730825284},{0.700568793943,0.713584868781},{0.702754744457,0.711432195745},{0.704934080376,0.709272826439}
,{0.707106781187,0.707106781187},{0.709272826439,0.704934080376},{0.711432195745,0.702754744457},{0.713584868781,0.700568793943}
,{0.715730825284,0.698376249409},{0.717870045056,0.696177131491},{0.720002507961,0.693971460890},{0.722128193929,0.691759258364}
,{0.724247082951,0.689540544737},{0.726359155084,0.687315340892},{0.728464390448,0.685083667773},{0.730562769228,0.682845546385}
,{0.732654271672,0.680600997795},{0.734738878096,0.678350043130},{0.736816568877,0.676092703575},{0.738887324461,0.673829000379}
,{0.740951125355,0.671558954847},{0.743007952135,0.669282588347},{0.745057785441,0.666999922304},{0.747100605980,0.664710978203}
,{0.749136394523,0.662415777590},{0.751165131910,0.660114342067},{0.753186799044,0.657806693297},{0.755201376897,0.655492853000}
,{0.757208846506,0.653172842954},{0.759209188978,0.650846684996},{0.761202385484,0.648514401022},{0.763188417263,0.646176012983}
,{0.765167265622,0.643831542890},{0.767138911936,0.641481012809},{0.769103337646,0.639124444864},{0.771060524262,0.636761861236}
,{0.773010453363,0.634393284164},{0.774953106595,0.632018735940},{0.776888465673,0.629638238915},{0.778816512381,0.627251815495}
,{0.780737228572,0.624859488142},{0.782650596167,0.622461279374},{0.784556597156,0.620057211763},{0.786455213599,0.617647307938}
,{0.788346427627,0.615231590581},{0.790230221437,0.612810082429},{0.792106577300,0.610382806276},{0.793975477554,0.607949784968}
,{0.795836904609,0.605511041404},{0.797690840943,0.603066598540},{0.799537269108,0.600616479384},{0.801376171723,0.598160706996}
,{0.803207531481,0.595699304492},{0.805031331143,0.593232295040},{0.806847553544,0.590759701859},{0.808656181588,0.588281548223}
,{0.810457198253,0.585797857456},{0.812250586585,0.583308652938},{0.814036329706,0.580813958096},{0.815814410807,0.578313796412}
,{0.817584813152,0.575808191418},{0.819347520077,0.573297166698},{0.821102514991,0.570780745887},{0.822849781376,0.568258952670}
,{0.824589302785,0.565731810784},{0.826321062846,0.563199344014},{0.828045045258,0.560661576197},{0.829761233795,0.558118531221}
,{0.831469612303,0.555570233020},{0.833170164702,0.553016705580},{0.834862874986,0.550457972937},{0.836547727224,0.547894059173}
,{0.838224705555,0.545324988422},{0.839893794196,0.542750784865},{0.841554977437,0.540171472730},{0.843208239642,0.537587076296}
,{0.844853565250,0.534997619887},{0.846490938774,0.532403127877},{0.848120344803,0.529803624686},{0.849741768001,0.527199134782}
,{0.851355193105,0.524589682678},{0.852960604930,0.521975292937},{0.854557988365,0.519355990166},{0.856147328375,0.516731799018}
,{0.857728610000,0.514102744193},{0.859301818357,0.511468850438},{0.860866938638,0.508830142543},{0.862423956111,0.506186645345}
,{0.863972856122,0.503538383726},{0.865513624091,0.500885382611},{0.867046245516,0.498227666973},{0.868570705971,0.495565261826}
,{0.870086991109,0.492898192230},{0.871595086656,0.490226483288},{0.873094978418,0.487550160148},{0.874586652278,0.484869248001}
,{0.876070094195,0.482183772079},{0.877545290207,0.479493757660},{0.879012226429,0.476799230063},{0.880470889052,0.474100214651}
,{0.881921264348,0.471396736826},{0.883363338666,0.468688822036},{0.884797098431,0.465976495768},{0.886222530149,0.463259783552}
,{0.887639620403,0.460538710958},{0.889048355855,0.457813303599},{0.890448723245,0.455083587126},{0.891840709392,0.452349587234}
,{0.893224301196,0.449611329655},{0.894599485631,0.446868840162},{0.895966249756,0.444122144570},{0.897324580705,0.441371268732}
,{0.898674465694,0.438616238539},{0.900015892016,0.435857079922},{0.901348847046,0.433093818853},{0.902673318237,0.430326481340}
,{0.903989293123,0.427555093430},{0.905296759318,0.424779681209},{0.906595704515,0.422000270800},{0.907886116488,0.419216888363}
,{0.909167983091,0.416429560098},{0.910441292258,0.413638312238},{0.911706032005,0.410843171058},{0.912962190428,0.408044162865}
,{0.914209755704,0.405241314005},{0.915448716088,0.402434650859},{0.916679059921,0.399624199846},{0.917900775621,0.396809987417}
,{0.919113851690,0.393992040061},{0.920318276709,0.391170384302},{0.921514039342,0.388345046699},{0.922701128334,0.385516053844}
,{0.923879532511,0.382683432365},{0.925049240783,0.379847208924},{0.926210242138,0.377007410216},{0.927362525650,0.374164062971}
,{0.928506080473,0.371317193952},{0.929640895843,0.368466829953},{0.930766961079,0.365612997805},{0.931884265582,0.362755724367}
,{0.932992798835,0.359895036535},{0.934092550404,0.357030961233},{0.935183509939,0.354163525420},{0.936265667170,0.351292756086}
,{0.937339011913,0.348418680249},{0.938403534063,0.345541324964},{0.939459223602,0.342660717312},{0.940506070593,0.339776884407}
,{0.941544065183,0.336889853392},{0.942573197601,0.333999651442},{0.943593458162,0.331106305760},{0.944604837261,0.328209843579}
,{0.945607325381,0.325310292162},{0.946600913083,0.322407678801},{0.947585591018,0.319502030816},{0.948561349916,0.316593375556}
,{0.949528180593,0.313681740399},{0.950486073949,0.310767152750},{0.951435020969,0.307849640042},{0.952375012720,0.304929229735}
,{0.953306040354,0.302005949319},{0.954228095109,0.299079826308},{0.955141168306,0.296150888244},{0.956045251350,0.293219162694}
,{0.956940335732,0.290284677254},{0.957826413028,0.287347459545},{0.958703474896,0.284407537211},{0.959571513082,0.281464937926}
,{0.960430519416,0.278519689385},{0.961280485811,0.275571819311},{0.962121404269,0.272621355450},{0.962953266874,0.269668325573}
,{0.963776065795,0.266712757475},{0.964589793290,0.263754678975},{0.965394441698,0.260794117915},{0.966190003445,0.257831102162}
,{0.966976471045,0.254865659605},{0.967753837093,0.251897818154},{0.968522094274,0.248927605746},{0.969281235357,0.245955050336}
,{0.970031253195,0.242980179903},{0.970772140729,0.240003022449},{0.971503890986,0.237023605994},{0.972226497079,0.234041958584}
,{0.972939952206,0.231058108281},{0.973644249651,0.228072083171},{0.974339382786,0.225083911360},{0.975025345067,0.222093620973}
,{0.975702130039,0.219101240157},{0.976369731330,0.216106797076},{0.977028142658,0.213110319916},{0.977677357825,0.210111836880}
,{0.978317370720,0.207111376192},{0.978948175319,0.204108966093},{0.979569765685,0.201104634842},{0.980182135968,0.198098410718}
,{0.980785280403,0.195090322016},{0.981379193314,0.192080397050},{0.981963869110,0.189068664150},{0.982539302287,0.186055151663}
,{0.983105487431,0.183039887955},{0.983662419212,0.180022901406},{0.984210092387,0.177004220412},{0.984748501802,0.173983873387}
,{0.985277642389,0.170961888760},{0.985797509168,0.167938294975},{0.986308097245,0.164913120490},{0.986809401814,0.161886393780}
,{0.987301418158,0.158858143334},{0.987784141645,0.155828397654},{0.988257567731,0.152797185258},{0.988721691960,0.149764534677}
,{0.989176509965,0.146730474455},{0.989622017463,0.143695033150},{0.990058210262,0.140658239333},{0.990485084256,0.137620121586}
,{0.990902635428,0.134580708507},{0.991310859846,0.131540028703},{0.991709753669,0.128498110794},{0.992099313142,0.125454983412}
,{0.992479534599,0.122410675199},{0.992850414460,0.119365214811},{0.993211949235,0.116318630912},{0.993564135521,0.113270952178}
,{0.993906970002,0.110222207294},{0.994240449453,0.107172424957},{0.994564570734,0.104121633872},{0.994879330795,0.101069862755}
,{0.995184726672,0.098017140330},{0.995480755492,0.094963495330},{0.995767414468,0.091908956497},{0.996044700901,0.088853552583}
,{0.996312612183,0.085797312344},{0.996571145791,0.082740264549},{0.996820299291,0.079682437971},{0.997060070339,0.076623861392}
,{0.997290456679,0.073564563600},{0.997511456140,0.070504573390},{0.997723066644,0.067443919564},{0.997925286199,0.064382630930}
,{0.998118112900,0.061320736302},{0.998301544934,0.058258264500},{0.998475580573,0.055195244350},{0.998640218180,0.052131704680}
,{0.998795456205,0.049067674327},{0.998941293187,0.046003182131},{0.999077727753,0.042938256935},{0.999204758618,0.039872927588}
,{0.999322384588,0.036807222941},{0.999430604555,0.033741171851},{0.999529417501,0.030674803177},{0.999618822495,0.027608145779}
,{0.999698818696,0.024541228523},{0.999769405351,0.021474080275},{0.999830581796,0.018406729906},{0.999882347454,0.015339206285}
,{0.999924701839,0.012271538286},{0.999957644552,0.009203754782},{0.999981175283,0.006135884649},{0.999995293810,0.003067956763}
,{1.000000000000,0.000000000000}};

enum {
    LOOKUP_BITS				= 8,							
    EXP_POS			        = 23,							
    EXP_BIAS				= 127,							
    LOOKUP_POS				= (EXP_POS-LOOKUP_BITS),
    SEED_POS				= (EXP_POS-8),
    SQRT_TABLE_SIZE			= (2<<LOOKUP_BITS),
    LOOKUP_MASK				= (SQRT_TABLE_SIZE-1)
};
typedef uint32_t dword;
union _flint {
    dword i;
    float f;
};

static int32_t iSqrt[SQRT_TABLE_SIZE];
static bool InitSqrtTable( void );
static bool bSqrtTableInited = InitSqrtTable();
static bool InitSqrtTable( void )
{
    union _flint fi, fo;

    for ( int i = 0; i < SQRT_TABLE_SIZE; i++ ) {
        fi.i	 = ((EXP_BIAS-1) << EXP_POS) | (i << LOOKUP_POS);
        fo.f	 = (float)( 1.0 / sqrt( fi.f ) );
        iSqrt[i] = ((dword)(((fo.i + (1<<(SEED_POS-2))) >> SEED_POS) & 0xFF))<<SEED_POS;
    }
    
    iSqrt[SQRT_TABLE_SIZE / 2] = ((dword)(0xFF))<<(SEED_POS); 

    return true;
}

Real Fabs(Real v)
{
    return fabs(v);
}

Real FMod(Real v,Real n)
{
    Int32 q = v / n;

    return (v - q * n);
}

static Real CosImpl(Real theta)
{
    return cosf(theta);
    Int32 tableIdx = theta * SIN_COS_ITEM_COUNT / PI_DIV_2;
    Real frac = theta - tableIdx * TABLE_INTERVAL;
    
    return SIN_COS_TABLE[tableIdx][1] 
           + frac * (SIN_COS_TABLE[(tableIdx) + 1][1] - SIN_COS_TABLE[(tableIdx)][1]);
}

static Real SinImpl(Real theta)
{
    return sinf(theta);
    Int32 tableIdx = theta * SIN_COS_ITEM_COUNT / PI_DIV_2;
    Real frac = theta - tableIdx * TABLE_INTERVAL;
    
    return SIN_COS_TABLE[tableIdx][0] 
           + frac * (SIN_COS_TABLE[(tableIdx) + 0][0] - SIN_COS_TABLE[(tableIdx)][0]);
}

Real Cos(Real  theta)
{
    theta = FMod(theta,PI2);        
    if(theta < 0)
    {
        theta += PI2;
    }

    if(theta <= PI_DIV_2)
    {
        return CosImpl(theta);
    }
    else if(theta <= PI)
    {
        return -SinImpl(theta - PI_DIV_2);
    }
    else if(theta <= PI3_DIV_2)
    {
        return -CosImpl(theta - PI);
    }
    else
    {
        return SinImpl(theta - PI3_DIV_2);
    }
}

Real Sin(Real theta)
{
    theta = FMod(theta,PI2);        
    if(theta < 0)
    {
        theta += PI2;
    }

    if(theta <= PI_DIV_2)
    {
        return SinImpl(theta);
    }
    else if(theta <= PI)
    {
        return CosImpl(theta - PI_DIV_2);
    }
    else if(theta <= PI3_DIV_2)
    {
        return -SinImpl(theta - PI);
    }
    else
    {
        return -CosImpl(theta - PI3_DIV_2);
    }
}

Real Sqrt(Real x)
{
    if(x < 0)
    {
        throw NoDefinedOp();
    }
    
    return x * InvSqrt( x );
//    union
//    {
//        int intPart;
//        float floatPart;
//    } convertor;
//
//    union
//    {
//        int intPart;
//        float floatPart;
//    } convertor2;
//    convertor.floatPart = (x);
//    convertor2.floatPart = (x);
//    convertor.intPart = 0x1FBCF800 + (convertor.intPart >> 1);
//    convertor2.intPart = 0x5f3759df - (convertor2.intPart >> 1);
//    return 0.5f*(convertor.floatPart + (x * convertor2.floatPart));
}

Real InvSqrt(Real v)
{
    if(v < 0)
    {
        throw NoDefinedOp();
    }
//    Real xhalf = 0.5f*x;
//    int64_t i = *(int64_t*)&x;
//    i = 0x5fe6ec85e7de30da - (i >> 1);        // 计算第一个近似根
//    x = *(Real*)&i;
//    x = x*(1.5f - xhalf*x*x);       // 牛顿迭代法
//    x = x*(1.5f - xhalf*x*x);       // 牛顿迭代法
//    return x;
    float x = v;
    dword a = ((union _flint*)(&x))->i;
    union _flint seed;

    double y = x * 0.5f;
    seed.i = (( ( (3*EXP_BIAS-1) - ( (a >> EXP_POS) & 0xFF) ) >> 1)<<EXP_POS) | iSqrt[(a >> (EXP_POS-LOOKUP_BITS)) & LOOKUP_MASK];
    double r = seed.f;
    r = r * ( 1.5f - r * r * y );
    r = r * ( 1.5f - r * r * y );
    r = r * ( 1.5f - r * r * y );
    return r;
}

Real ACos(Real v)
{
    if ( v <= -1.0f ) 
    {
        return PI;
    }
    else if ( v >= 1.0f )
    {
        return 0.0f;
    }
    else
    {
        return acosf(v);
    }
}

Real Tan(Real x)
{
    return tanf(x);
}

Real Cot(Real x)
{
    return 1 / tanf(x);
}
Real ASin(Real v)
{
    Real thetha;
    return thetha;
}

Real ATan(Real v)
{
    Real thetha;
    return thetha;
}

Int32 Round(Real v)
{
    static double magic = 6755399441055744.0;
    v += magic;
    return *(int*)&v;
    
//    return Int32(GetValue(v + 0.5));
}

Real Pow(Real e,Int32 nPow)
{
    if(0 == nPow)
    {
	return 1.0;
    }
    else if(1 == nPow)
    {
	return e;
    }
    else
    {
	if(0 == nPow % 2)
	{
	    return Pow(e,nPow/2) * Pow(e,nPow/2);
	}
	else
	{
	    return Pow(e,nPow/2) * Pow(e,nPow/2) * e;
	}
    }
}

Int32 RandRange(Int32 a,Int32 b)
{
    assert( b > a);

    Int32 nInterval = b - a;
    return a + (std::rand() % (nInterval + 1));
}

