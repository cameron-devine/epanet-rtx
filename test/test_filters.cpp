#include <math.h>

#include "test_main.h"
#include "TimeSeriesFilter.h"
#include "FailoverTimeSeries.h"
#include "ValidRangeTimeSeries.h"
#include "DbPointRecord.h"
#include "ConcreteDbRecords.h"

using namespace RTX;
using namespace std;

////////////////////////
// units
BOOST_AUTO_TEST_SUITE(filters)

BOOST_AUTO_TEST_CASE(complex_resampler) {

  // https://xyleminc.atlassian.net/browse/VUEWNO-3597
  // reproduce an error with resampled output:
  // raw->failover->validrange->resample
  
  // time ranges
  time_t origin(1643616000);
  time_t ONE_DAY(60*60*24);
  
  // data set
  DbPointRecord::_sp db(new SqlitePointRecord());
  db->setConnectionString("sample_dataset.db");
  Clock::_sp c5m(new Clock(60*5, 0));
  
  TimeSeries::_sp raw(new TimeSeries("raw", RTX_FOOT));
  raw->setRecord(db);
  raw->insertPoints({ Point(1643616049,14.703218460083008),
                      Point(1643616109,14.708871841430664),
                      Point(1643616169,14.711383819580078),
                      Point(1643616229,14.713897705078125),
                      Point(1643616349,14.719551086425781),
                      Point(1643616409,14.716409683227539),
                      Point(1643616469,14.708871841430664),
                      Point(1643616529,14.716409683227539),
                      Point(1643616589,14.718921661376953),
                      Point(1643616649,14.73274040222168),
                      Point(1643616769,14.708244323730469),
                      Point(1643616829,14.722063064575195),
                      Point(1643616889,14.727716445922852),
                      Point(1643616949,14.727087020874023),
                      Point(1643617009,14.727716445922852),
                      Point(1643617069,14.721433639526367),
                      Point(1643617129,14.724575042724609),
                      Point(1643617189,14.725202560424805),
                      Point(1643617249,14.730855941772461),
                      Point(1643617309,14.735252380371094),
                      Point(1643617369,14.73274040222168),
                      Point(1643617549,14.727087020874023),
                      Point(1643617609,14.730228424072266),
                      Point(1643617669,14.724575042724609),
                      Point(1643617729,14.727716445922852),
                      Point(1643617789,14.72960090637207),
                      Point(1643617849,14.727716445922852),
                      Point(1643617909,14.730228424072266),
                      Point(1643618029,14.713897705078125),
                      Point(1643618089,14.745931625366211),
                      Point(1643618149,14.717037200927734),
                      Point(1643618209,14.730228424072266),
                      Point(1643618269,14.727716445922852),
                      Point(1643618329,14.724575042724609),
                      Point(1643618389,14.735881805419922),
                      Point(1643618449,14.71452522277832),
                      Point(1643618509,14.730228424072266),
                      Point(1643618569,14.724575042724609),
                      Point(1643618629,14.728343963623047),
                      Point(1643618689,14.730228424072266),
                      Point(1643618749,14.727087020874023),
                      Point(1643618809,14.71452522277832),
                      Point(1643618869,14.708871841430664),
                      Point(1643618929,14.711383819580078),
                      Point(1643618989,14.70635986328125),
                      Point(1643619049,14.711383819580078),
                      Point(1643619110,14.710756301879883),
                      Point(1643619170,14.706987380981445),
                      Point(1643619230,14.70635986328125),
                      Point(1643619290,14.697565078735352),
                      Point(1643619350,14.70635986328125),
                      Point(1643619470,14.706987380981445),
                      Point(1643619530,14.708871841430664),
                      Point(1643619590,14.701333999633789),
                      Point(1643619650,14.703218460083008),
                      Point(1643619710,14.687515258789062),
                      Point(1643619830,14.685630798339844),
                      Point(1643619890,14.687515258789062),
                      Point(1643620010,14.685003280639648),
                      Point(1643620130,14.671184539794922),
                      Point(1643620190,14.682489395141602),
                      Point(1643620250,14.685003280639648),
                      Point(1643620310,14.678722381591797),
                      Point(1643620370,14.671184539794922),
                      Point(1643620490,14.663017272949219),
                      Point(1643620550,14.660505294799805),
                      Point(1643620610,14.6611328125),
                      Point(1643620670,14.660505294799805),
                      Point(1643620730,14.657993316650391),
                      Point(1643620790,14.660505294799805),
                      Point(1643620850,14.657993316650391),
                      Point(1643620910,14.655481338500977),
                      Point(1643620970,14.64982795715332),
                      Point(1643621030,14.641033172607422),
                      Point(1643621090,14.636636734008789),
                      Point(1643621150,14.636009216308594),
                      Point(1643621210,14.636636734008789),
                      Point(1643621270,14.639148712158203),
                      Point(1643621390,14.642290115356445),
                      Point(1643621450,14.64166259765625),
                      Point(1643621510,14.625957489013672),
                      Point(1643621570,14.646686553955078),
                      Point(1643621630,14.639148712158203),
                      Point(1643621690,14.642290115356445),
                      Point(1643621750,14.643547058105469),
                      Point(1643621810,14.644802093505859),
                      Point(1643621870,14.647314071655273),
                      Point(1643621930,14.633495330810547),
                      Point(1643621990,14.657993316650391),
                      Point(1643622050,14.644802093505859),
                      Point(1643622170,14.668670654296875),
                      Point(1643622230,14.655481338500977),
                      Point(1643622290,14.64982795715332),
                      Point(1643622350,14.644174575805664),
                      Point(1643622410,14.644802093505859),
                      Point(1643622470,14.642917633056641),
                      Point(1643622530,14.644802093505859),
                      Point(1643622590,14.64982795715332),
                      Point(1643622710,14.652339935302734),
                      Point(1643622770,14.634124755859375),
                      Point(1643622830,14.647314071655273),
                      Point(1643622890,14.652339935302734),
                      Point(1643622950,14.64982795715332),
                      Point(1643623010,14.652339935302734),
                      Point(1643623070,14.647314071655273),
                      Point(1643623130,14.644174575805664),
                      Point(1643623190,14.646686553955078),
                      Point(1643623250,14.64982795715332),
                      Point(1643623310,14.649198532104492),
                      Point(1643623430,14.64166259765625),
                      Point(1643623490,14.642290115356445),
                      Point(1643623550,14.636009216308594),
                      Point(1643623610,14.64166259765625),
                      Point(1643623670,14.646686553955078),
                      Point(1643623730,14.642917633056641),
                      Point(1643623790,14.644802093505859),
                      Point(1643623850,14.64166259765625),
                      Point(1643623910,14.64982795715332),
                      Point(1643623970,14.647314071655273),
                      Point(1643624030,14.64982795715332),
                      Point(1643624090,14.647314071655273),
                      Point(1643624150,14.65296745300293),
                      Point(1643624210,14.647943496704102),
                      Point(1643624270,14.660505294799805),
                      Point(1643624330,14.657993316650391),
                      Point(1643624390,14.652339935302734),
                      Point(1643624570,14.660505294799805),
                      Point(1643624630,14.667415618896484),
                      Point(1643624690,14.654851913452148),
                      Point(1643624750,14.669300079345703),
                      Point(1643624810,14.646686553955078),
                      Point(1643624870,14.659877777099609),
                      Point(1643624990,14.660505294799805),
                      Point(1643625050,14.669300079345703),
                      Point(1643625110,14.665531158447266),
                      Point(1643625170,14.668670654296875),
                      Point(1643625230,14.673696517944336),
                      Point(1643625290,14.679349899291992),
                      Point(1643625350,14.685003280639648),
                      Point(1643625410,14.681861877441406),
                      Point(1643625470,14.690027236938477),
                      Point(1643625530,14.689399719238281),
                      Point(1643625590,14.693168640136719),
                      Point(1643625650,14.692541122436523),
                      Point(1643625710,14.695053100585938),
                      Point(1643625770,14.690027236938477),
                      Point(1643625830,14.692541122436523),
                      Point(1643625890,14.690027236938477),
                      Point(1643625950,14.695053100585938),
                      Point(1643626010,14.693168640136719),
                      Point(1643626070,14.687515258789062),
                      Point(1643626130,14.70635986328125),
                      Point(1643626190,14.682489395141602),
                      Point(1643626250,14.695680618286133),
                      Point(1643626310,14.690656661987305),
                      Point(1643626370,14.708871841430664),
                      Point(1643626430,14.698192596435547),
                      Point(1643626490,14.695053100585938),
                      Point(1643626550,14.692541122436523),
                      Point(1643626610,14.695680618286133),
                      Point(1643626730,14.722690582275391),
                      Point(1643626790,14.71452522277832),
                      Point(1643626850,14.70635986328125),
                      Point(1643626910,14.705730438232422),
                      Point(1643626970,14.717037200927734),
                      Point(1643627030,14.71452522277832),
                      Point(1643627090,14.702590942382812),
                      Point(1643627150,14.727716445922852),
                      Point(1643627210,14.725202560424805),
                      Point(1643627270,14.724575042724609),
                      Point(1643627330,14.725831985473633),
                      Point(1643627390,14.722063064575195),
                      Point(1643627450,14.717037200927734),
                      Point(1643627510,14.724575042724609),
                      Point(1643627570,14.717037200927734),
                      Point(1643627630,14.735252380371094),
                      Point(1643627690,14.727716445922852),
                      Point(1643627750,14.741535186767578),
                      Point(1643627810,14.735252380371094),
                      Point(1643627870,14.733367919921875),
                      Point(1643627930,14.730228424072266),
                      Point(1643627990,14.733367919921875),
                      Point(1643628050,14.730228424072266),
                      Point(1643628110,14.735881805419922),
                      Point(1643628230,14.738393783569336),
                      Point(1643628290,14.744047164916992),
                      Point(1643628350,14.733997344970703),
                      Point(1643628410,14.738393783569336),
                      Point(1643628470,14.735881805419922),
                      Point(1643628590,14.746559143066406),
                      Point(1643628650,14.74090576171875),
                      Point(1643628711,14.743419647216797),
                      Point(1643628770,14.746559143066406),
                      Point(1643628831,14.745931625366211),
                      Point(1643628891,14.748443603515625),
                      Point(1643628951,14.739650726318359),
                      Point(1643629011,14.74090576171875),
                      Point(1643629071,14.735881805419922),
                      Point(1643629131,14.74090576171875),
                      Point(1643629251,14.737766265869141),
                      Point(1643629311,14.741535186767578),
                      Point(1643629371,14.740278244018555),
                      Point(1643629431,14.74090576171875),
                      Point(1643629491,14.744047164916992),
                      Point(1643629551,14.749073028564453),
                      Point(1643629611,14.743419647216797),
                      Point(1643629671,14.727716445922852),
                      Point(1643629731,14.754096984863281),
                      Point(1643629791,14.735881805419922),
                      Point(1643629851,14.74090576171875),
                      Point(1643629911,14.743419647216797),
                      Point(1643629971,14.786760330200195),
                      Point(1643630031,14.979597091674805),
                      Point(1643630091,15.209493637084961),
                      Point(1643630151,15.401073455810547),
                      Point(1643630211,15.588886260986328),
                      Point(1643630271,15.757852554321289),
                      Point(1643630331,15.945035934448242),
                      Point(1643630391,16.050561904907227),
                      Point(1643630451,16.157344818115234),
                      Point(1643630511,16.252193450927734),
                      Point(1643630571,16.326940536499023),
                      Point(1643630631,16.401687622070312),
                      Point(1643630691,16.453195571899414),
                      Point(1643630751,16.500934600830078),
                      Point(1643630811,16.53045654296875),
                      Point(1643630871,16.583847045898438),
                      Point(1643630931,16.624675750732422),
                      Point(1643630991,16.643520355224609),
                      Point(1643631051,16.646032333374023),
                      Point(1643631111,16.694398880004883),
                      Point(1643631171,16.718267440795898),
                      Point(1643631231,16.742763519287109),
                      Point(1643631291,16.753442764282227),
                      Point(1643631351,16.752815246582031),
                      Point(1643631471,16.769775390625),
                      Point(1643631531,16.788618087768555),
                      Point(1643631591,16.782964706420898),
                      Point(1643631651,16.793643951416016),
                      Point(1643631711,16.809974670410156),
                      Point(1643631831,16.801181793212891),
                      Point(1643631891,16.8043212890625),
                      Point(1643631951,16.825677871704102),
                      Point(1643632011,16.828189849853516),
                      Point(1643632071,16.833215713500977),
                      Point(1643632131,16.833843231201172),
                      Point(1643632191,16.831331253051758),
                      Point(1643632251,16.833843231201172),
                      Point(1643632311,16.855199813842773),
                      Point(1643632371,16.857711791992188),
                      Point(1643632431,16.86085319519043),
                      Point(1643632551,16.857711791992188),
                      Point(1643632611,16.863365173339844),
                      Point(1643632671,16.86085319519043),
                      Point(1643632791,16.863365173339844),
                      Point(1643632851,16.86085319519043),
                      Point(1643632911,16.860225677490234),
                      Point(1643632971,16.857711791992188),
                      Point(1643633031,16.844522476196289),
                      Point(1643633151,16.842010498046875),
                      Point(1643633211,16.838869094848633),
                      Point(1643633331,16.83447265625),
                      Point(1643633391,16.836357116699219),
                      Point(1643633571,16.838869094848633),
                      Point(1643633751,16.836357116699219),
                      Point(1643633811,16.821281433105469),
                      Point(1643633871,16.814371109008789),
                      Point(1643633931,16.811859130859375),
                      Point(1643633991,16.814371109008789),
                      Point(1643634171,16.815000534057617),
                      Point(1643634231,16.817512512207031),
                      Point(1643634291,16.816883087158203),
                      Point(1643634411,16.815000534057617),
                      Point(1643634471,16.817512512207031),
                      Point(1643634531,16.814371109008789),
                      Point(1643634591,16.811859130859375),
                      Point(1643634651,16.814371109008789),
                      Point(1643634711,16.801181793212891),
                      Point(1643634771,16.798040390014648),
                      Point(1643634831,16.795528411865234),
                      Point(1643634891,16.793014526367188),
                      Point(1643634951,16.789875030517578),
                      Point(1643635011,16.793014526367188),
                      Point(1643635071,16.792387008666992),
                      Point(1643635191,16.795528411865234),
                      Point(1643635251,16.792387008666992),
                      Point(1643635371,16.794898986816406),
                      Point(1643635431,16.78924560546875),
                      Point(1643635491,16.79615592956543),
                      Point(1643635551,16.795528411865234),
                      Point(1643635611,16.78924560546875),
                      Point(1643635671,16.789875030517578),
                      Point(1643635731,16.788618087768555),
                      Point(1643635791,16.775426864624023),
                      Point(1643635851,16.771030426025391),
                      Point(1643635911,16.776683807373047),
                      Point(1643635971,16.776056289672852),
                      Point(1643636031,16.774171829223633),
                      Point(1643636091,16.773542404174805),
                      Point(1643636211,16.771030426025391),
                      Point(1643636271,16.776056289672852),
                      Point(1643636331,16.770402908325195),
                      Point(1643636391,16.772914886474609),
                      Point(1643636451,16.773542404174805),
                      Point(1643636511,16.772287368774414),
                      Point(1643636571,16.773542404174805),
                      Point(1643636631,16.776056289672852),
                      Point(1643636811,16.773542404174805),
                      Point(1643636871,16.776056289672852),
                      Point(1643636931,16.776683807373047),
                      Point(1643636991,16.775426864624023),
                      Point(1643637111,16.776056289672852),
                      Point(1643637171,16.778568267822266),
                      Point(1643637231,16.777938842773438),
                      Point(1643637291,16.78108024597168),
                      Point(1643637351,16.778568267822266),
                      Point(1643637411,16.874671936035156),
                      Point(1643637471,17.059970855712891),
                      Point(1643637531,17.287982940673828),
                      Point(1643637591,17.475166320800781),
                      Point(1643637651,17.637226104736328),
                      Point(1643637711,17.797399520874023),
                      Point(1643637771,17.931819915771484),
                      Point(1643637831,18.065610885620117),
                      Point(1643637891,18.158575057983398),
                      Point(1643637951,18.264728546142578),
                      Point(1643638011,18.336963653564453),
                      Point(1643638071,18.417366027832031),
                      Point(1643638131,18.470756530761719),
                      Point(1643638191,18.524776458740234),
                      Point(1643638251,18.576282501220703),
                      Point(1643638311,18.626533508300781),
                      Point(1643638371,18.653543472290039),
                      Point(1643638432,18.688718795776367),
                      Point(1643638492,18.718240737915039),
                      Point(1643638552,18.735828399658203),
                      Point(1643638612,18.74964714050293),
                      Point(1643638672,18.787336349487305),
                      Point(1643638732,18.801155090332031),
                      Point(1643638792,18.830047607421875),
                      Point(1643638852,18.833189010620117),
                      Point(1643638912,18.827535629272461),
                      Point(1643638972,18.828163146972656),
                      Point(1643639032,18.830047607421875),
                      Point(1643639152,18.830677032470703),
                      Point(1643639272,18.832561492919922),
                      Point(1643639392,18.830677032470703),
                      Point(1643639452,18.830047607421875),
                      Point(1643639512,18.832561492919922),
                      Point(1643639572,18.833189010620117),
                      Point(1643639632,18.832561492919922),
                      Point(1643639692,18.835073471069336),
                      Point(1643639752,18.835700988769531),
                      Point(1643639812,18.835073471069336),
                      Point(1643639932,18.835700988769531),
                      Point(1643639992,18.835073471069336),
                      Point(1643640052,18.83758544921875),
                      Point(1643640112,18.835700988769531),
                      Point(1643640172,18.83758544921875),
                      Point(1643640232,18.835073471069336),
                      Point(1643640412,18.850776672363281),
                      Point(1643640472,18.856430053710938),
                      Point(1643640532,18.862083435058594),
                      Point(1643640592,18.861455917358398),
                      Point(1643640652,18.862083435058594),
                      Point(1643640712,18.861455917358398),
                      Point(1643640772,18.864595413208008),
                      Point(1643640892,18.863967895507812),
                      Point(1643641072,18.869621276855469),
                      Point(1643641132,18.885951995849609),
                      Point(1643641192,18.89097785949707),
                      Point(1643641252,18.887836456298828),
                      Point(1643641312,18.89097785949707),
                      Point(1643641372,18.889720916748047),
                      Point(1643641432,18.89097785949707),
                      Point(1643641612,18.896003723144531),
                      Point(1643641672,18.914846420288086),
                      Point(1643641732,18.920499801635742),
                      Point(1643641792,18.917987823486328),
                      Point(1643641852,18.915473937988281),
                      Point(1643641912,18.9173583984375),
                      Point(1643641972,18.914846420288086),
                      Point(1643642032,18.909820556640625),
                      Point(1643642092,18.892862319946289),
                      Point(1643642152,18.893489837646484),
                      Point(1643642272,18.896003723144531),
                      Point(1643642392,18.89097785949707),
                      Point(1643642452,18.871505737304688),
                      Point(1643642512,18.865852355957031),
                      Point(1643642632,18.866479873657227),
                      Point(1643642692,18.871505737304688),
                      Point(1643642752,18.868991851806641),
                      Point(1643642812,18.863340377807617),
                      Point(1643642872,18.841983795166016),
                      Point(1643642932,18.84449577331543),
                      Point(1643643052,18.843868255615234),
                      Point(1643643112,18.841983795166016),
                      Point(1643643172,18.843868255615234),
                      Point(1643643232,18.849521636962891),
                      Point(1643643292,18.847007751464844),
                      Point(1643643352,18.847637176513672),
                      Point(1643643412,18.843868255615234),
                      Point(1643643472,18.841354370117188),
                      Point(1643643532,18.84449577331543),
                      Point(1643643592,18.839469909667969),
                      Point(1643643652,18.836330413818359),
                      Point(1643643712,18.828163146972656),
                      Point(1643643832,18.823139190673828),
                      Point(1643643892,18.814346313476562),
                      Point(1643643952,18.819999694824219),
                      Point(1643644012,18.821882247924805),
                      Point(1643644072,18.819999694824219),
                      Point(1643644132,18.823139190673828),
                      Point(1643644192,18.819999694824219),
                      Point(1643644252,18.816858291625977),
                      Point(1643644312,18.819370269775391),
                      Point(1643644372,18.821882247924805),
                      Point(1643644432,18.822511672973633),
                      Point(1643644672,18.819370269775391),
                      Point(1643644732,18.821882247924805),
                      Point(1643644852,18.818115234375),
                      Point(1643644912,18.827535629272461),
                      Point(1643644972,18.843868255615234),
                      Point(1643645032,18.840726852416992),
                      Point(1643645092,18.851406097412109),
                      Point(1643645152,18.848892211914062),
                      Point(1643645212,18.846380233764648),
                      Point(1643645272,18.848264694213867),
                      Point(1643645332,18.846380233764648),
                      Point(1643645392,18.848892211914062),
                      Point(1643645752,18.856430053710938),
                      Point(1643645812,18.87590217590332),
                      Point(1643645872,18.875274658203125),
                      Point(1643645992,18.87590217590332),
                      Point(1643646052,18.877786636352539),
                      Point(1643646172,18.880928039550781),
                      Point(1643646232,18.882183074951172),
                      Point(1643646292,18.891605377197266),
                      Point(1643646352,18.904796600341797),
                      Point(1643646412,18.907308578491211),
                      Point(1643646532,18.907936096191406),
                      Point(1643646592,18.904796600341797),
                      Point(1643646652,18.904167175292969),
                      Point(1643646712,18.907308578491211),
                      Point(1643646772,18.906681060791016),
                      Point(1643646832,18.909820556640625),
                      Point(1643646892,18.907308578491211),
                      Point(1643647072,18.907936096191406),
                      Point(1643647132,18.904167175292969),
                      Point(1643647192,18.907308578491211),
                      Point(1643647252,18.909820556640625),
                      Point(1643647312,18.904167175292969),
                      Point(1643647372,18.906681060791016),
                      Point(1643647432,18.904167175292969),
                      Point(1643647492,18.901655197143555),
                      Point(1643647552,18.896631240844727),
                      Point(1643647612,18.8828125),
                      Point(1643647792,18.885951995849609),
                      Point(1643647853,18.8828125),
                      Point(1643647913,18.879671096801758),
                      Point(1643647973,18.8828125),
                      Point(1643648033,18.879671096801758),
                      Point(1643648093,18.8828125),
                      Point(1643648153,18.880298614501953),
                      Point(1643648213,18.8828125),
                      Point(1643826491,18.90919303894043),
                      Point(1643826551,18.907936096191406)
  });
  
  FailoverTimeSeries::_sp failover(new FailoverTimeSeries());
  failover->source(raw)->units(RTX_FOOT)->name("failover");
  
  ValidRangeTimeSeries::_sp vr(new ValidRangeTimeSeries());
  vr->range(0, 1500)->mode(RTX::ValidRangeTimeSeries::drop)->source(failover)->units(RTX_FOOT)->name("valid_range");
  
  TimeSeriesFilter::_sp rs(new TimeSeriesFilter());
  rs->resample(ResampleModeLinear)->source(vr)->c(c5m)->units(RTX_FOOT)->name("resample");
  
  auto points = rs->points(TimeRange(origin, origin+ONE_DAY));
  
  BOOST_CHECK_EQUAL(points.size(), ONE_DAY/(5*60));
  
  
}


BOOST_AUTO_TEST_SUITE_END()
// filters
/////////////////////////
