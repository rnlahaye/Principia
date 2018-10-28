
#pragma once

#include "numerics/fixed_arrays.hpp"

namespace principia {
namespace numerics {

// Global maxima over [-1, 1] of the absolute value of the normalized associated
// Legendre functions.
constexpr FixedLowerTriangularMatrix<double, 21>
MaxAbsNormalizedAssociatedLegendreFunction{{{
    /*n= 0, m= 0*/1.00000'00000'00000'00000'00000'00000'00000'00000'00000'00000,
    /*n= 1, m= 0*/1.73205'08075'68877'29352'74463'41505'87236'69428'05253'81038,
    /*      m= 1*/1.73205'08075'68877'29352'74463'41505'87236'69428'05253'81038,
    /*n= 2, m= 0*/2.23606'79774'99789'69640'91736'68731'27623'54406'18359'61153,
    /*      m= 1*/1.93649'16731'03708'44258'96326'99891'19980'54164'60852'64580,
    /*      m= 2*/1.93649'16731'03708'44258'96326'99891'19980'54164'60852'64580,
    /*n= 3, m= 0*/2.64575'13110'64590'59050'16157'53639'26042'57102'59183'08245,
    /*      m= 1*/2.23109'34040'90868'12794'17920'68760'49997'17141'74318'12979,
    /*      m= 2*/1.97202'65943'66538'68085'57760'97187'20568'28051'67076'93145,
    /*      m= 3*/2.09165'00663'35188'86994'54300'64462'96872'34820'38423'24668,
    /*n= 4, m= 0*/3.00000'00000'00000'00000'00000'00000'00000'00000'00000'00000,
    /*      m= 1*/2.50458'61007'88660'05019'30285'36950'61431'45439'25975'71322,
    /*      m= 2*/2.15620'84068'74797'20725'17031'80562'30208'41748'81989'62540,
    /*      m= 3*/2.03784'98549'32889'79942'91871'47101'99914'85665'81185'51298,
    /*      m= 4*/2.21852'99186'62356'01596'27481'09335'60639'31558'12961'54788,
    /*n= 5, m= 0*/3.31662'47903'55399'84911'49327'36670'68668'39270'88545'58935,
    /*      m= 1*/2.75540'89147'23569'38447'07343'76879'99674'44797'55290'99895,
    /*      m= 2*/2.34651'60898'18401'14021'85184'15120'49408'04537'07534'87619,
    /*      m= 3*/2.16159'06351'74494'38317'06658'42636'74951'64561'53096'77543,
    /*      m= 4*/2.10599'14529'74109'29449'75331'93779'91429'46102'10438'61308,
    /*      m= 5*/2.32681'38086'23285'61177'49828'66646'77669'37229'86985'76155,
    /*n= 6, m= 0*/3.60555'12754'63989'29311'92212'67470'49594'62512'96573'84525,
    /*      m= 1*/2.98718'40709'14500'76551'20994'16183'43382'80677'17603'78274,
    /*      m= 2*/2.52953'12253'38112'69465'82104'07414'81114'65083'29458'05949,
    /*      m= 3*/2.30482'61159'66398'55811'27181'45540'94935'46898'35063'91749,
    /*      m= 4*/2.18994'30702'86835'74185'63397'29162'59536'33026'24943'18307,
    /*      m= 5*/2.17122'36872'01521'19102'26959'36849'19651'26466'79755'25126,
    /*      m= 6*/2.42182'45962'49695'37140'20443'90976'28090'81884'01535'36534,
    /*n= 7, m= 0*/3.87298'33462'07416'88517'92653'99782'39961'08329'21705'29159,
    /*      m= 1*/3.20325'61705'00479'87021'09300'43493'52142'42622'87418'86510,
    /*      m= 2*/2.70339'90045'45792'53368'86811'33638'91016'45372'38548'31628,
    /*      m= 3*/2.44880'98620'63929'79513'39744'51328'44442'17182'16156'03857,
    /*      m= 4*/2.30156'77675'94381'36290'04220'15292'94145'89340'87633'60097,
    /*      m= 5*/2.22632'97411'31023'23431'33311'71008'30444'45889'42530'70886,
    /*      m= 6*/2.23253'83418'31358'59814'51223'30576'33934'71407'64148'26030,
    /*      m= 7*/2.50682'66169'60175'80800'21243'91383'80912'21170'20230'94131,
    /*n= 8, m= 0*/4.12310'56256'17660'54982'14098'55974'07702'51471'99225'37362,
    /*      m= 1*/3.40625'05064'81265'00404'21054'31975'02246'17924'47735'30086,
    /*      m= 2*/2.86848'75791'65682'75518'25977'00249'88106'91580'77415'35154,
    /*      m= 3*/2.58906'56919'76033'31951'88044'54756'53202'51577'38052'20279,
    /*      m= 4*/2.41897'26169'43740'31925'56439'62373'80813'43813'34798'39009,
    /*      m= 5*/2.31476'81479'25394'84794'94346'52283'12605'54681'23979'17406,
    /*      m= 6*/2.26542'81620'58176'82125'57020'94840'60039'88161'07586'82385,
    /*      m= 7*/2.28998'13747'07906'15001'27982'44823'59961'92779'89056'18530,
    /*      m= 8*/2.58397'77317'09147'29537'52615'20290'15910'87273'32700'30691,
    /*n= 9, m= 0*/4.35889'89435'40673'55223'69819'83859'61565'91370'03925'23244,
    /*      m= 1*/3.59819'12796'05711'49149'66900'13092'91701'94982'19419'33356,
    /*      m= 2*/3.02562'63254'97909'31378'80559'64532'67853'26029'14808'02422,
    /*      m= 3*/2.72445'38277'43382'53826'88571'41559'80633'99487'09347'73882,
    /*      m= 4*/2.53613'24630'27390'62646'60835'50657'36088'04180'23074'56067,
    /*      m= 5*/2.41247'55090'58048'58734'62438'51391'71168'13499'05955'62954,
    /*      m= 6*/2.33589'05445'33605'75070'44196'04434'19151'17572'61014'58971,
    /*      m= 7*/2.30503'03549'13013'19365'47708'13476'06119'94998'10506'63250,
    /*      m= 8*/2.34387'37900'11022'55223'43763'89710'62722'59065'72192'92180,
    /*      m= 9*/2.65478'47521'17980'09151'47942'46868'22232'70791'57529'58139,
    /*n=10, m= 0*/4.58257'56949'55840'00658'80471'93728'00848'89844'56576'76797,
    /*      m= 1*/3.78065'42932'10653'19617'78689'40908'84724'89544'65115'88899,
    /*      m= 2*/3.17567'28659'18381'76010'67873'17402'40435'61489'85169'45624,
    /*      m= 3*/2.85485'25894'88105'21907'94363'67607'77921'87899'20198'59121,
    /*      m= 4*/2.65099'56885'29539'57732'60565'23524'04355'03281'51004'92536,
    /*      m= 5*/2.51238'64493'84272'06859'89454'64933'68358'49235'69301'80674,
    /*      m= 6*/2.41821'22397'25581'33291'20430'72826'67418'37329'67788'18717,
    /*      m= 7*/2.36100'91137'13119'33793'84581'94667'08817'45278'76898'66756,
    /*      m= 8*/2.34414'90858'75517'63646'06627'14974'19606'15985'62838'34021,
    /*      m= 9*/2.39458'49819'84191'16494'24001'48389'07930'68325'52246'88068,
    /*      m=10*/2.72034'48649'17319'86249'34570'55648'32846'12285'09549'19612,
    /*n=11, m= 0*/4.79583'15233'12719'54159'74380'64162'69391'99967'07041'90413,
    /*      m= 1*/3.95488'57660'89513'97962'76771'51393'47514'40192'22661'65798,
    /*      m= 2*/3.31940'22445'64563'34036'88727'23424'51355'83950'81709'77592,
    /*      m= 3*/2.98048'05648'90970'05064'66129'37117'69811'09475'47637'02646,
    /*      m= 4*/2.76285'07473'00780'39116'65860'88651'62346'94140'46936'63108,
    /*      m= 5*/2.61183'53550'57980'12081'61678'06614'55460'00654'38040'62545,
    /*      m= 6*/2.50456'56751'74031'44179'25196'62540'86331'55990'46813'51411,
    /*      m= 7*/2.43086'78590'28726'30218'59547'55016'16918'58732'49389'75639,
    /*      m= 8*/2.38812'10025'64252'90410'55137'12902'49152'99853'74548'95630,
    /*      m= 9*/2.38233'54132'78143'69871'73394'39148'95825'00549'05424'38979,
    /*      m=10*/2.44246'36765'15136'57037'26376'64836'13040'49194'18944'69325,
    /*      m=11*/2.78148'38439'70260'79958'04550'82441'67355'64902'81900'52168,
    /*n=12, m= 0*/5.00000'00000'00000'00000'00000'00000'00000'00000'00000'00000,
    /*      m= 1*/4.12188'74887'84155'09918'88330'55246'01917'72198'89887'17564,
    /*      m= 2*/3.45748'69077'72449'23696'86688'60270'84769'40233'85858'61395,
    /*      m= 3*/3.10166'26708'95588'36996'79532'39486'80095'53685'97626'36356,
    /*      m= 4*/2.87151'06390'15471'70293'73525'16811'04068'97313'91538'32157,
    /*      m= 5*/2.70970'88178'99392'33683'54394'16921'98254'46721'85725'52850,
    /*      m= 6*/2.59183'94319'45757'91822'76089'26230'16920'79054'77819'18549,
    /*      m= 7*/2.50618'45711'37644'96940'81765'70372'93799'92339'95870'87565,
    /*      m= 8*/2.44760'91226'92112'62001'30723'77486'24819'30127'72754'59432,
    /*      m= 9*/2.41613'24414'22779'01912'27059'24069'85396'86151'93630'79035,
    /*      m=10*/2.41939'65356'17980'31048'19489'60684'38615'53813'36328'53440,
    /*      m=11*/2.48781'93313'56543'75790'71545'35549'45883'06735'31720'59116,
    /*      m=12*/2.83884'00606'34283'17030'17261'31741'28441'12964'15612'24254,
    /*n=13, m= 0*/5.19615'24227'06631'88058'23390'24517'61710'08284'15761'43114,
    /*      m= 1*/4.28247'71607'36588'48142'07827'86487'98928'79935'45875'18180,
    /*      m= 2*/3.58962'33813'13897'96262'78013'41713'23071'13289'45825'49685,
    /*      m= 3*/3.21874'23647'94189'41559'31552'12977'35894'36741'81388'33334,
    /*      m= 4*/2.97700'88530'72592'82804'80646'20305'97762'70323'59904'94412,
    /*      m= 5*/2.80553'96529'49501'98255'59089'75229'09499'18658'83000'27738,
    /*      m= 6*/2.67862'76314'96376'85166'16057'16983'39255'56323'08103'73962,
    /*      m= 7*/2.58350'54659'39902'18602'61448'50370'75354'12349'48628'83703,
    /*      m= 8*/2.51370'60169'29990'01200'14692'56217'87465'02519'54046'31608,
    /*      m= 9*/2.46680'96922'66173'72768'67049'69642'91936'26140'86876'40106,
    /*      m=10*/2.44441'87234'47053'02391'95531'39203'56266'90680'04651'71083,
    /*      m=11*/2.45526'74287'98561'06735'90508'70715'85553'31760'42789'75438,
    /*      m=12*/2.53092'04419'38643'79792'03595'04146'45919'34273'08154'36176,
    /*      m=13*/2.89291'80638'39265'46459'50360'39902'19171'08814'18978'77144,
    /*n=14, m= 0*/5.38516'48071'34504'03125'07104'91540'32955'62951'20161'64479,
    /*      m= 1*/4.43733'15065'17453'11602'52077'10198'68022'92627'66274'02467,
    /*      m= 2*/3.71894'39805'06565'20740'48898'36360'92746'53984'30183'69354,
    /*      m= 3*/3.33204'81753'04993'79891'24885'09080'24599'78549'77773'91569,
    /*      m= 4*/3.07947'22336'37524'69098'29270'16894'72702'34673'23217'35829,
    /*      m= 5*/2.89915'72518'61889'02288'26038'30802'68710'13755'18964'51642,
    /*      m= 6*/2.76425'77457'99934'38413'55234'98277'00567'67821'80485'97990,
    /*      m= 7*/2.66120'09088'09931'72978'46147'86763'27527'02247'92897'70971,
    /*      m= 8*/2.58268'33898'78465'52544'96746'30202'22582'07709'69197'08896,
    /*      m= 9*/2.52504'94586'10044'96007'49583'79724'19159'68988'37695'25357,
    /*      m=10*/2.48748'49318'76899'45987'25043'46757'73051'51599'58907'36188,
    /*      m=11*/2.47261'31821'13948'78733'91311'62397'57217'28722'38684'29236,
    /*      m=12*/2.48994'82750'71162'08110'54058'53927'72970'97504'02270'08698,
    /*      m=13*/2.57199'82721'09038'20700'00683'09843'42381'68795'10743'19245,
    /*      m=14*/2.94412'41287'79572'84972'43138'60854'42800'29626'55215'51817,
    /*n=15, m= 0*/5.56776'43628'30021'92211'94712'98918'54952'04763'93377'57041,
    /*      m= 1*/4.58701'75440'73773'73840'94654'30317'68497'62280'64287'33383,
    /*      m= 2*/3.84323'26864'83800'37832'70332'64142'02652'68097'10049'09111,
    /*      m= 3*/3.44188'19726'01982'21251'54296'87996'55240'08657'87569'25416,
    /*      m= 4*/3.17906'38697'05443'83114'89645'80929'84209'47495'12399'66580,
    /*      m= 5*/2.99053'48252'17977'63351'19793'18190'86624'43502'14042'34556,
    /*      m= 6*/2.84840'82936'67147'12209'64714'67836'32534'48838'79454'76732,
    /*      m= 7*/2.73844'09727'56174'98008'28595'21608'42325'93986'60770'43049,
    /*      m= 8*/2.65273'35716'42070'46839'39412'19983'58407'60387'65165'70716,
    /*      m= 9*/2.58689'57742'22481'55314'56159'60016'66274'49461'50798'36636,
    /*      m=10*/2.53892'14327'94606'61559'91384'37549'95147'47527'20222'49740,
    /*      m=11*/2.50901'48062'57731'86376'21045'66256'56500'59814'09367'94252,
    /*      m=12*/2.50049'81148'19435'48914'21708'25694'87199'58061'28039'80769,
    /*      m=13*/2.52347'23947'07706'21669'27183'35860'15307'11576'33044'84640,
    /*      m=14*/2.61125'19079'89449'65657'27283'94659'96844'64367'61325'59628,
    /*      m=15*/2.99279'06344'83276'85041'50532'87996'37412'40139'26891'34790,
    /*n=16, m= 0*/5.74456'26465'38028'65985'06114'68218'92931'82202'64457'98279,
    /*      m= 1*/4.73201'56340'73245'75523'67493'64217'50814'43167'71028'31862,
    /*      m= 2*/3.96373'42717'29440'50795'67349'30105'71775'89526'50712'02473,
    /*      m= 3*/3.54851'62534'55311'35195'13677'26490'29248'28410'56443'59758,
    /*      m= 4*/3.27595'64083'26132'49410'51638'00348'35424'16137'30619'14770,
    /*      m= 5*/3.07971'67827'29878'24349'86403'73358'70129'40024'26810'64188,
    /*      m= 6*/2.93093'79021'70990'02613'94017'46366'37777'02236'91345'74994,
    /*      m= 7*/2.81478'79956'60791'60557'58439'31166'86840'87441'67782'41822,
    /*      m= 8*/2.72290'16131'59440'79927'19133'77620'76624'64021'60874'69795,
    /*      m= 9*/2.65039'47748'27659'83117'11360'31175'49137'02786'18406'31557,
    /*      m=10*/2.59457'82978'45859'02915'83058'38422'78755'63569'82951'17158,
    /*      m=11*/2.55448'32706'76294'51064'90130'56297'25641'72590'98089'44145,
    /*      m=12*/2.53099'73235'22108'90427'01345'12490'85763'71978'79077'41969,
    /*      m=13*/2.52794'50236'69038'47643'73565'82515'35549'83315'67502'16052,
    /*      m=14*/2.55588'92208'69008'26888'14481'94271'37662'72514'69690'42592,
    /*      m=15*/2.64885'31845'39488'95963'05085'02682'70989'02105'70102'20088,
    /*      m=16*/3.03919'32564'47120'50490'28755'80902'24941'15491'35561'47996,
    /*n=17, m= 0*/5.91607'97830'99616'04256'73282'91561'61704'84155'01230'79434,
    /*      m= 1*/4.87273'67471'41771'81889'16378'62366'75919'10183'60437'30379,
    /*      m= 2*/4.08076'53966'99602'92553'93596'85043'76962'63520'95072'30792,
    /*      m= 3*/3.65219'51367'31473'82929'48949'74850'57133'68887'92034'95080,
    /*      m= 4*/3.37031'94828'71897'98371'24388'58698'12153'54798'64826'64155,
    /*      m= 5*/3.16678'21344'26006'35322'96821'03276'27095'95225'81218'64988,
    /*      m= 6*/3.01180'17039'67975'79417'19945'26317'38785'15040'78971'31508,
    /*      m= 7*/2.89001'18572'48400'35742'80051'10000'93966'28489'37183'66253,
    /*      m= 8*/2.79265'74275'63576'43571'87674'96356'77387'87466'44640'39662,
    /*      m= 9*/2.71448'92826'55783'28849'54618'78176'24648'71922'67866'95942,
    /*      m=10*/2.65237'84867'59694'25390'32707'60404'43217'91462'77121'63582,
    /*      m=11*/2.60469'97988'93920'32926'52052'85578'76655'60503'93480'39411,
    /*      m=12*/2.57117'31179'51184'39168'68599'28298'37404'35208'40510'72529,
    /*      m=13*/2.55316'62831'23895'12662'88217'17475'73705'19727'79453'46850,
    /*      m=14*/2.55488'03252'82961'30426'71562'91653'15197'49292'73739'53682,
    /*      m=15*/2.58725'50589'68814'31254'38286'29859'68100'99223'76893'72583,
    /*      m=16*/2.68495'10267'31912'20002'54747'24190'31703'80349'72739'27735,
    /*      m=17*/3.08356'33882'16997'49876'12377'29231'31272'92468'23653'84709,
    /*n=18, m= 0*/6.08276'25302'98219'68899'96842'45202'06706'20849'70094'78641,
    /*      m= 1*/5.00953'55985'77719'11067'22555'06877'67071'82382'26146'42916,
    /*      m= 2*/4.19460'23834'77051'46882'44741'27641'53125'45695'20343'48708,
    /*      m= 3*/3.75313'67661'95361'57827'99698'03457'42696'64293'56094'63550,
    /*      m= 4*/3.46231'39920'49558'73094'21551'17097'36595'53508'28771'54290,
    /*      m= 5*/3.25182'53137'10879'67839'49887'06035'91858'15656'95085'88009,
    /*      m= 6*/3.09100'77028'56419'74388'50317'02900'25880'63261'11082'23209,
    /*      m= 7*/2.96399'81161'53808'47998'35365'53302'80989'28385'24781'54982,
    /*      m= 8*/2.86170'00633'39406'99993'95357'05112'99639'14897'42063'62018,
    /*      m= 9*/2.77857'36951'25825'88610'55854'63726'79590'78206'58829'36337,
    /*      m=10*/2.71117'91955'97000'28975'33560'62490'36040'41629'54133'43624,
    /*      m=11*/2.65748'13441'38239'47225'27955'58398'01775'39450'24210'13155,
    /*      m=12*/2.61655'71406'27976'87556'51151'36346'53891'02490'97494'89746,
    /*      m=13*/2.58860'47462'87029'19055'10132'53893'36255'41158'95705'75682,
    /*      m=14*/2.57534'28577'36345'03473'02355'60252'31688'46132'56315'04793,
    /*      m=15*/2.58126'49259'97209'05277'93089'78956'52361'42847'80285'73491,
    /*      m=16*/2.61762'80277'92017'20518'98819'66106'36834'55412'02051'35815,
    /*      m=17*/2.71967'51205'55511'11626'33041'47449'89639'19427'83958'33699,
    /*      m=18*/3.12609'73062'74295'86820'22439'80741'71818'49342'67626'01834,
    /*n=19, m= 0*/6.24499'79983'98398'20584'68931'20939'79446'10729'59977'99166,
    /*      m= 1*/5.14272'07822'96203'10618'66528'04247'87484'20597'67324'69485,
    /*      m= 2*/4.30548'77531'15269'25371'94159'93268'22817'16435'99943'33640,
    /*      m= 3*/3.85153'61049'11929'49678'87579'56775'10048'04237'26416'74287,
    /*      m= 4*/3.55208'97961'10271'04174'17382'42265'02395'44825'42472'30952,
    /*      m= 5*/3.33494'59047'00214'79121'58734'87112'47960'63026'05075'42944,
    /*      m= 6*/3.16859'28854'33606'00010'41237'09818'73452'24633'89172'16852,
    /*      m= 7*/3.03669'91006'26662'68865'03382'14773'52212'74951'75018'42256,
    /*      m= 8*/2.92985'93216'96627'93933'68868'18961'94684'44158'12353'14349,
    /*      m= 9*/2.84228'91151'38744'34139'67646'64544'72996'21653'83539'95457,
    /*      m=10*/2.77031'17272'08963'61979'74150'60371'35891'62095'83943'09091,
    /*      m=11*/2.71161'19202'90663'64056'02510'30079'15892'86120'62393'14285,
    /*      m=12*/2.66487'34913'26214'88972'77488'19462'03913'58724'99698'83268,
    /*      m=13*/2.62965'76312'30690'53973'40373'81320'90421'78715'04362'09711,
    /*      m=14*/2.60650'71888'11554'01755'58598'45475'33199'09854'21831'87044,
    /*      m=15*/2.59740'59534'72476'19075'01139'46292'12748'09994'69050'45621,
    /*      m=16*/2.60708'16800'62398'28956'92694'57375'33209'81432'49158'14640,
    /*      m=17*/2.64706'53118'06739'55869'01018'66723'80669'45094'94844'07814,
    /*      m=18*/2.75313'89624'21653'11055'54683'26562'18253'92260'01019'96639,
    /*      m=19*/3.16696'30578'15221'91021'55433'10698'47448'82489'59935'43949,
    /*n=20, m= 0*/6.40312'42374'32848'68648'82176'74621'81326'45204'20132'62102,
    /*      m= 1*/5.27256'26923'59066'49014'52518'73736'77913'36903'55961'65223,
    /*      m= 2*/4.41363'55437'26841'58910'11992'38257'16426'30287'30094'24950,
    /*      m= 3*/3.94756'76806'43579'29498'18602'67343'55383'74166'00453'40384,
    /*      m= 4*/3.63978'51332'30688'76694'79680'08412'01007'39554'96698'28072,
    /*      m= 5*/3.41624'31138'23167'12599'70734'94905'06595'44044'65507'33995,
    /*      m= 6*/3.24460'96814'28802'07652'64594'33360'76129'56383'82887'17960,
    /*      m= 7*/3.10810'64875'76248'27373'67925'42741'42782'62797'48451'39567,
    /*      m= 8*/2.99704'27119'26895'30325'86981'06769'84447'86592'40178'19292,
    /*      m= 9*/2.90541'96192'30738'46933'75806'21392'11016'22252'50064'30276,
    /*      m=10*/2.82936'87851'06589'10333'16369'44677'34007'07754'45786'11436,
    /*      m=11*/2.76636'91046'73147'72741'73788'67686'55767'54325'25539'85450,
    /*      m=12*/2.71484'25596'98433'56454'31084'42562'98408'57115'35900'56370,
    /*      m=13*/2.67396'64951'91157'25102'92801'28189'55144'91180'35043'70001,
    /*      m=14*/2.64364'82956'18434'95383'33340'82786'93024'16101'60128'77734,
    /*      m=15*/2.62468'72739'08871'63226'01867'32766'52473'75376'66550'93218,
    /*      m=16*/2.61927'34634'31558'71250'27901'51156'89079'47905'39654'69538,
    /*      m=17*/2.63232'74947'67672'64343'48975'25809'46842'56384'99496'78315,
    /*      m=18*/2.67562'17171'06700'39132'57984'57633'64931'93963'18498'35830,
    /*      m=19*/2.78544'23746'67732'24569'69647'04179'62867'24438'54061'74642,
    /*      m=20*/3.20630'57222'92479'56821'71274'41330'55401'41456'04937'99744,
}}};

}  // namespace numerics
}  // namespace principia
