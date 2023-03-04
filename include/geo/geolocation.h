///////////////////////////////////////////////////////////////////
// Name:        geolocation.h
// Purpose:     Geographical data for places mentioned in the Bible.
// Copyright:   David Reynolds
//              Data generated from merged.txt at OpenBible.info.
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef GEOLOCATION_H
#define GEOLOCATION_H

#include "../sowerbase.h"
#include "../../include/string/string.h"
#include <wx/choice.h>
#include <wx/listctrl.h>

struct SwGeoCoordinates
{
    swFloat latitude;
    swFloat longitude;

    void operator = (const SwGeoCoordinates & coords)
    {
        latitude = coords.latitude;
        longitude = coords.longitude;
    }
};

struct SwGeoData
{
    const char * name;
    swUI32 id;
    SwGeoCoordinates coords;
};

struct SwGeoConversionData
{
    swUI32      mapwidth;
    swUI32      mapheight;
    swFloat     latitudeTop;
    swFloat     latitudeBottom;
    swFloat     longitudeLeft;
    swFloat     longitudeRight;

    void operator = (const SwGeoConversionData & cd)
    {
        mapwidth = cd.mapwidth;
        mapheight = cd.mapheight;
        latitudeTop = cd.latitudeTop;
        latitudeBottom = cd.latitudeBottom;
        longitudeLeft = cd.longitudeLeft;
        longitudeRight = cd.longitudeRight;
    }

    void SetCoordinates(swFloat latTop, swFloat latBottom, swFloat longLeft, swFloat longRight)
    {
        latitudeTop = latTop;
        latitudeBottom = latBottom;
        longitudeLeft = longLeft;
        longitudeRight = longRight;
    }

    void SetMapSize(swUI32 height, swUI32 width)
    {
        mapheight = height;
        mapwidth = width;
    }

    void Reset()
    {
        mapwidth = 0;
        mapheight = 0;
        latitudeTop = 0;
        latitudeBottom = 0;
        longitudeLeft = 0;
        longitudeRight = 0;
    }
};

// Changes here should also be made in 'GeolocationData'.
enum GEO_LOCATIONS
{
    GEO_UNKNOWN, GEO_ABANA, GEO_ABARIM, GEO_ABDON, GEO_ABEL,
    GEO_ABEL__BETH__MAACAH, GEO_ABEL__KERAMIM, GEO_ABEL__MAIM, GEO_ABEL__MEHOLAH, GEO_ABEL__SHITTIM,
    GEO_ABIEZER, GEO_ABILENE, GEO_ABRONAH, GEO_ACCAD, GEO_ACCO,
    GEO_ACHAIA, GEO_ACHSHAPH, GEO_ACHZIB, GEO_ADADAH, GEO_ADAM,
    GEO_ADAMI__NEKEB, GEO_ADDAR, GEO_ADITHAIM, GEO_ADMAH, GEO_ADORAIM,
    GEO_ADRAMYTTIUM, GEO_ADRIATIC_SEA, GEO_ADULLAM, GEO_ADUMMIM, GEO_AENON,
    GEO_AHAVA, GEO_AHLAB, GEO_AI, GEO_AIATH, GEO_AIJA,
    GEO_AIJALON, GEO_AIN, GEO_AKELDAMA, GEO_AKRABBIM, GEO_ALEMETH,
    GEO_ALEXANDRIA, GEO_ALLAMMELECH, GEO_ALLON__BACUTH, GEO_ALMON, GEO_ALMON__DIBLATHAIM,
    GEO_ALUSH, GEO_AMAD, GEO_AMALEK, GEO_AMAM, GEO_AMANA,
    GEO_AMAW, GEO_AMMAH, GEO_AMMON, GEO_AMPHIPOLIS, GEO_ANAB,
    GEO_ANAHARATH, GEO_ANATHOTH, GEO_ANEM, GEO_ANER, GEO_ANGLE,
    GEO_ANIM, GEO_ANTIOCH, GEO_ANTIPATRIS, GEO_APHEK, GEO_APHEKAH,
    GEO_APHIK, GEO_APOLLONIA, GEO_AR, GEO_ARAB, GEO_ARABAH,
    GEO_ARABIA, GEO_ARAD, GEO_ARAM, GEO_ARAM__MAACAH, GEO_ARAM__NAHARAIM,
    GEO_ARAM__ZOBAH, GEO_ARARAT, GEO_AREOPAGUS, GEO_ARGOB, GEO_ARIEL,
    GEO_ARMAGEDDON, GEO_ARNON, GEO_AROER, GEO_ARPAD, GEO_ARUBBOTH,
    GEO_ARUMAH, GEO_ARVAD, GEO_ASHAN, GEO_ASHDOD, GEO_ASHKELON,
    GEO_ASHKENAZ, GEO_ASHNAH, GEO_ASHTAROTH, GEO_ASHTEROTH__KARNAIM, GEO_ASIA,
    GEO_ASSHUR, GEO_ASSOS, GEO_ASSYRIA, GEO_ATAROTH, GEO_ATAROTH__ADDAR,
    GEO_ATHARIM, GEO_ATHENS, GEO_ATROTH__SHOPHAN, GEO_ATTALIA, GEO_AVEN,
    GEO_AVITH, GEO_AVVA, GEO_AVVIM, GEO_AYYAH, GEO_AZAL,
    GEO_AZEKAH, GEO_AZMAVETH, GEO_AZMON, GEO_AZNOTH__TABOR,
    GEO_AZOTUS, GEO_BAAL, GEO_BAAL__GAD, GEO_BAAL__HAMON, GEO_BAAL__HAZOR,
    GEO_BAAL__HERMON, GEO_BAAL__MEON, GEO_BAAL__PEOR, GEO_BAAL__PERAZIM, GEO_BAAL__SHALISHAH,
    GEO_BAAL__TAMAR, GEO_BAALAH, GEO_BAALATH, GEO_BAALATH__BEER, GEO_BABEL,
    GEO_BABYLON, GEO_BABYLONIA, GEO_BAHARUM, GEO_BAHURIM, GEO_BALAH,
    GEO_BAMAH, GEO_BAMOTH, GEO_BAMOTH__BAAL, GEO_BASHAN, GEO_BATH__RABBIM,
    GEO_BEALOTH, GEO_BEER, GEO_BEER__ELIM, GEO_BEER__LAHAI__ROI, GEO_BEEROTH,
    GEO_BEEROTH_BENE__JAAKAN, GEO_BEERSHEBA, GEO_BEESHTERAH, GEO_BELA, GEO_BENE__BERAK,
    GEO_BENE__JAAKAN, GEO_BEON, GEO_BEREA, GEO_BERED, GEO_BEROTHAH,
    GEO_BEROTHAI, GEO_BESOR, GEO_BETAH, GEO_BETEN, GEO_BETH__ANATH,
    GEO_BETH__ANOTH, GEO_BETH__ARABAH, GEO_BETH__ARBEL, GEO_BETH__AVEN, GEO_BETH__AZMAVETH,
    GEO_BETH__BAAL__MEON, GEO_BETH__BARAH, GEO_BETH__BIRI, GEO_BETH__CAR, GEO_BETH__DAGON,
    GEO_BETH__DIBLATHAIM, GEO_BETH__EDEN, GEO_BETH__EKED, GEO_BETH__EMEK, GEO_BETH__EZEL,
    GEO_BETH__GAMUL, GEO_BETH__GILGAL, GEO_BETH__HACCHEREM, GEO_BETH__HAGGAN, GEO_BETH__HARAM,
    GEO_BETH__HARAN, GEO_BETH__HOGLAH, GEO_BETH__HORON, GEO_BETH__JESHIMOTH, GEO_BETH__LE__APHRAH,
    GEO_BETH__LEBAOTH, GEO_BETH__MAACAH, GEO_BETH__MARCABOTH, GEO_BETH__MEON, GEO_BETH__MILLO,
    GEO_BETH__NIMRAH, GEO_BETH__PAZZEZ, GEO_BETH__PELET, GEO_BETH__PEOR, GEO_BETH__REHOB,
    GEO_BETH__SHAN, GEO_BETH__SHEAN, GEO_BETH__SHEMESH, GEO_BETH__SHITTAH, GEO_BETH__TAPPUAH,
    GEO_BETH__TOGARMAH, GEO_BETH__ZUR, GEO_BETHANY, GEO_BETHEL, GEO_BETHESDA,
    GEO_BETHLEHEM, GEO_BETHLEHEM_EPHRATHAH, GEO_BETHPHAGE, GEO_BETHSAIDA, GEO_BETHUEL,
    GEO_BETHUL, GEO_BETONIM, GEO_BEZEK, GEO_BEZER, GEO_BILEAM,
    GEO_BILHAH, GEO_BITHYNIA, GEO_BIZIOTHIAH, GEO_BOR__ASHAN, GEO_BOZEZ,
    GEO_BOZKATH, GEO_BOZRAH, GEO_BROAD_WALL, GEO_BUZ, GEO_CABBON,
    GEO_CABUL, GEO_CAESAREA, GEO_CAESAREA_PHILIPPI, GEO_CALNEH, GEO_CALNO,
    GEO_CANA, GEO_CANAAN, GEO_CANNEH, GEO_CAPERNAUM, GEO_CAPHTOR,
    GEO_CAPPADOCIA, GEO_CARCHEMISH, GEO_CARMEL, GEO_CAUDA, GEO_CENCHREAE,
    GEO_CHALDEA, GEO_CHEBAR, GEO_CHEPHIRAH, GEO_CHERITH, GEO_CHERUB,
    GEO_CHESALON, GEO_CHESIL, GEO_CHESULLOTH, GEO_CHEZIB, GEO_CHILMAD,
    GEO_CHINNERETH, GEO_CHINNEROTH, GEO_CHIOS, GEO_CHISLOTH__TABOR, GEO_CHITLISH,
    GEO_CHORAZIN, GEO_CILICIA, GEO_CNIDUS, GEO_COLOSSAE, GEO_CORINTH,
    GEO_COS, GEO_COZEBA, GEO_CRETE, GEO_CUN, GEO_CUSH,
    GEO_CUSHAN, GEO_CUTH, GEO_CUTHAH, GEO_CYPRUS, GEO_CYRENE,
    GEO_DABBESHETH, GEO_DABERATH, GEO_DALMANUTHA, GEO_DALMATIA, GEO_DAMASCUS,
    GEO_DAN, GEO_DANNAH, GEO_DEBIR, GEO_DECAPOLIS, GEO_DEDAN,
    GEO_DERBE, GEO_DIBON, GEO_DIBON__GAD, GEO_DILEAN, GEO_DIMNAH,
    GEO_DIMONAH, GEO_DIZAHAB, GEO_DOPHKAH, GEO_DOR, GEO_DOTHAN,
    GEO_DUMAH, GEO_DURA, GEO_EAST, GEO_EBENEZER, GEO_EBEZ,
    GEO_EBRON, GEO_ECBATANA, GEO_EDER, GEO_EDOM,
    GEO_EDREI, GEO_EGLAIM, GEO_EGLON, GEO_EGYPT, GEO_EKRON,
    GEO_EL__BETHEL, GEO_EL__PARAN, GEO_ELAM, GEO_ELATH, GEO_ELEALEH,
    GEO_ELIM, GEO_ELISHAH, GEO_ELLASAR, GEO_ELON, GEO_ELONBETH__HANAN,
    GEO_ELOTH, GEO_ELTEKE, GEO_ELTEKEH, GEO_ELTEKON, GEO_ELTOLAD,
    GEO_EMEK__KEZIZ, GEO_EMMAUS, GEO_EN__DOR, GEO_EN__GANNIM, GEO_EN__HADDAH,
    GEO_EN__HAKKORE, GEO_EN__HAZOR, GEO_EN__MISHPAT, GEO_EN__RIMMON, GEO_EN__ROGEL,
    GEO_EN__SHEMESH, GEO_EN__TAPPUAH, GEO_ENAIM, GEO_ENAM, GEO_ENEGLAIM,
    GEO_ENGEDI, GEO_EPHAH, GEO_EPHES__DAMMIM, GEO_EPHESUS, GEO_EPHRAIM,
    GEO_EPHRATH, GEO_EPHRATHAH, GEO_EPHRON, GEO_ERECH, GEO_ESAU,
    GEO_ESEK, GEO_ESHAN, GEO_ESHTAOL, GEO_ESHTEMOA, GEO_ESHTEMOH,
    GEO_ETAM, GEO_ETH__KAZIN, GEO_ETHAM, GEO_ETHER, GEO_ETHIOPIA,
    GEO_EUPHRATES, GEO_EZEM, GEO_EZION__GEBER, GEO_GAASH, GEO_GABBATHA,
    GEO_GALATIA, GEO_GALEED, GEO_GALILEE, GEO_GALLIM, GEO_GAMAD,
    GEO_GAREB, GEO_GATH, GEO_GATH__HEPHER, GEO_GATH__RIMMON, GEO_GAZA,
    GEO_GEBA, GEO_GEBAL, GEO_GEBIM, GEO_GEDER, GEO_GEDERAH,
    GEO_GEDEROTH, GEO_GEDEROTHAIM, GEO_GEDOR, GEO_GELILOTH, GEO_GENNESARET,
    GEO_GERAR, GEO_GERUTH_CHIMHAM, GEO_GESHUR, GEO_GETHSEMANE, GEO_GEZER,
    GEO_GIAH, GEO_GIBBETHON, GEO_GIBEAH, GEO_GIBEATH__ELOHIM, GEO_GIBEATH__HAARALOTH,
    GEO_GIBEON, GEO_GIDOM, GEO_GILBOA, GEO_GILEAD, GEO_GILGAL,
    GEO_GILO, GEO_GILOH, GEO_GIMZO, GEO_GITTAIM, GEO_GOAH,
    GEO_GOB, GEO_GOG, GEO_GOLAN, GEO_GOLGOTHA, GEO_GOMORRAH,
    GEO_GOSHEN, GEO_GOZAN, GEO_GREECE, GEO_GUR, GEO_GURBAAL,
    GEO_HABOR, GEO_HADAD__RIMMON, GEO_HADASHAH, GEO_HADID, GEO_HADRACH,
    GEO_HAELEPH, GEO_HAKKEPHIRIM, GEO_HALAH, GEO_HALHUL, GEO_HALI,
    GEO_HAM, GEO_HAMATH, GEO_HAMATH__ZOBAH, GEO_HAMMATH, GEO_HAMMON,
    GEO_HAMMOTH__DOR, GEO_HAMONAH, GEO_HANES, GEO_HANNATHON, GEO_HARA,
    GEO_HARADAH, GEO_HARAN, GEO_HARMON, GEO_HAROD, GEO_HAROSHETH__HAGOYIM,
    GEO_HASHMONAH, GEO_HAURAN, GEO_HAVVOTH__JAIR, GEO_HAZAR__ADDAR, GEO_HAZAR__ENAN,
    GEO_HAZAR__GADDAH, GEO_HAZAR__SHUAL, GEO_HAZAR__SUSAH, GEO_HAZAR__SUSIM, GEO_HAZAZON__TAMAR,
    GEO_HAZER__HATTICON, GEO_HAZEROTH, GEO_HAZOR, GEO_HAZOR__HADATTAH, GEO_HEBRON,
    GEO_HELAM, GEO_HELBAH, GEO_HELBON, GEO_HELECH, GEO_HELEPH,
    GEO_HELIOPOLIS, GEO_HELKATH, GEO_HELKATH__HAZZURIM, GEO_HENA, GEO_HEPHER,
    GEO_HERES, GEO_HERETH, GEO_HERMON, GEO_HESHBON, GEO_HESHMON,
    GEO_HETHLON, GEO_HEZRON, GEO_HIERAPOLIS, GEO_HILEN, GEO_HOBAH,
    GEO_HOLON, GEO_HOREB, GEO_HOREM, GEO_HORESH, GEO_HORMAH,
    GEO_HORONAIM, GEO_HOSAH, GEO_HUKKOK, GEO_HUKOK, GEO_HUMTAH,
    GEO_IBLEAM, GEO_ICONIUM, GEO_IDALAH, GEO_IDUMEA, GEO_IIM,
    GEO_IJON, GEO_ILLYRICUM, GEO_IMMER, GEO_INDIA, GEO_IPHTAH,
    GEO_IR__SHEMESH, GEO_IRPEEL, GEO_ITALY, GEO_ITHLAH, GEO_ITHNAN,
    GEO_ITURAEA, GEO_IVVAH, GEO_IYE__ABARIM, GEO_IYIM, GEO_JABBOK,
    GEO_JABESH, GEO_JABESH__GILEAD, GEO_JABEZ, GEO_JABNEEL, GEO_JABNEH,
    GEO_JAGUR, GEO_JAHAZ, GEO_JAHZAH, GEO_JAIR, GEO_JANIM,
    GEO_JANOAH, GEO_JAPHIA, GEO_JARMUTH, GEO_JATTIR, GEO_JAVAN,
    GEO_JAZER, GEO_JEBUS, GEO_JEBUSITE, GEO_JEGAR__SAHADUTHA, GEO_JEHUD,
    GEO_JEKABZEEL, GEO_JERICHO, GEO_JERUEL, GEO_JERUSALEM, GEO_JESHANAH,
    GEO_JESHIMON, GEO_JESHUA, GEO_JETUR, GEO_JEZREEL, GEO_JOGBEHAH,
    GEO_JOKDEAM, GEO_JOKMEAM, GEO_JOKNEAM, GEO_JOKTHEEL, GEO_JOPPA,
    GEO_JORDAN, GEO_JORDAN_VALLEY, GEO_JOTBAH, GEO_JOTBATHAH, GEO_JUDEA,
    GEO_JUTTAH, GEO_KABZEEL, GEO_KADESH, GEO_KADESH__BARNEA, GEO_KAIN,
    GEO_KAMON, GEO_KANAH, GEO_KARKA, GEO_KARKOR, GEO_KARNAIM,
    GEO_KARTAH, GEO_KARTAN, GEO_KATTATH, GEO_KEDAR, GEO_KEDEMOTH,
    GEO_KEDESH, GEO_KEDESH__NAPHTALI, GEO_KEHELATHAH, GEO_KEILAH, GEO_KENATH,
    GEO_KERIOTH, GEO_KERIOTH__HEZRON, GEO_KIBROTH__HATTAAVAH, GEO_KIBZAIM, GEO_KIDRON,
    GEO_KIDRON_VALLEY, GEO_KINAH, GEO_KIR, GEO_KIR__HARESETH, GEO_KIRIATH__ARBA,
    GEO_KIRIATH__HUZOTH, GEO_KIRIATH__SANNAH, GEO_KIRIATH__SEPHER, GEO_KIRIATHAIM, GEO_KISHION,
    GEO_KISHON, GEO_KITRON, GEO_KITTIM, GEO_KOA, GEO_KUE,
    GEO_LABAN, GEO_LACHISH, GEO_LAHMAM, GEO_LAISH, GEO_LAISHAH,
    GEO_LAKKUM, GEO_LAODICEA, GEO_LASEA, GEO_LASHA, GEO_LASHARON,
    GEO_LEB__KAMAI, GEO_LEBANON, GEO_LEBAOTH, GEO_LEBO__HAMATH, GEO_LEBONAH,
    GEO_LEHI, GEO_LESHEM, GEO_LIBNAH, GEO_LIBYA, GEO_LO__DEBAR,
    GEO_LOD, GEO_LUD, GEO_LUHITH, GEO_LUZ, GEO_LYCAONIA,
    GEO_LYCIA, GEO_LYDDA, GEO_LYSTRA, GEO_MAACAH, GEO_MAACATH,
    GEO_MAARATH, GEO_MAAREH__GEBA, GEO_MACEDONIA, GEO_MACHPELAH, GEO_MADMANNAH,
    GEO_MADMENAH, GEO_MADON, GEO_MAGADAN, GEO_MAGOG, GEO_MAHALAB,
    GEO_MAHANEH__DAN, GEO_MAKAZ, GEO_MAKHELOTH, GEO_MAKKEDAH, GEO_MALTA,
    GEO_MAMRE, GEO_MANAHATH, GEO_MAON, GEO_MARAH, GEO_MAREAL,
    GEO_MARESHAH, GEO_MAROTH, GEO_MASHAL, GEO_MASREKAH, GEO_MASSAH,
    GEO_MATTANAH, GEO_ME__JARKON, GEO_MEARAH, GEO_MECONAH, GEO_MEDEBA,
    GEO_MEDIA, GEO_MEGIDDO, GEO_MEMPHIS, GEO_MEPHAATH, GEO_MERATHAIM,
    GEO_MERIBAH, GEO_MERIBAH__KADESH, GEO_MEROM, GEO_MEROZ, GEO_MESHECH,
    GEO_MESHECH__TUBAL, GEO_MESOPOTAMIA, GEO_METHEG__AMMAH, GEO_MICHMAS, GEO_MICHMASH,
    GEO_MICHMETHATH, GEO_MIDDIN, GEO_MIDIAN, GEO_MIGDAL__EL, GEO_MIGDAL__GAD,
    GEO_MIGRON, GEO_MILETUS, GEO_MILLO, GEO_MINNI, GEO_MINNITH,
    GEO_MISHAL, GEO_MISREPHOTH__MAIM, GEO_MITHKAH, GEO_MITYLENE, GEO_MIZPAH,
    GEO_MIZPEH, GEO_MOAB, GEO_MOLADAH, GEO_MOREH, GEO_MORESHETH,
    GEO_MORESHETH__GATH, GEO_MORIAH, GEO_MORTAR, GEO_MOSERAH, GEO_MOSEROTH,
    GEO_MOUNT_BAAL__HERMON, GEO_MOUNT_BAALAH, GEO_MOUNT_CARMEL, GEO_MOUNT_EBAL, GEO_MOUNT_EPHRON,
    GEO_MOUNT_ESAU, GEO_MOUNT_GERIZIM, GEO_MOUNT_GILBOA, GEO_MOUNT_GILEAD, GEO_MOUNT_HERES,
    GEO_MOUNT_HERMON, GEO_MOUNT_HOR, GEO_MOUNT_HOREB, GEO_MOUNT_JEARIM, GEO_MOUNT_LEBANON,
    GEO_MOUNT_MIZAR, GEO_MOUNT_MORIAH, GEO_MOUNT_NEBO, GEO_MOUNT_OF_OLIVES, GEO_MOUNT_PARAN,
    GEO_MOUNT_PERAZIM, GEO_MOUNT_SEIR, GEO_MOUNT_SHEPHER, GEO_MOUNT_SINAI, GEO_MOUNT_SIRION,
    GEO_MOUNT_TABOR, GEO_MOUNT_ZALMON, GEO_MOUNT_ZEMARAIM, GEO_MOUNT_ZION, GEO_MOZAH,
    GEO_MYRA, GEO_MYSIA, GEO_NAAMAH, GEO_NAARAH, GEO_NAARAN,
    GEO_NAHALAL, GEO_NAHALOL, GEO_NAIN, GEO_NAIOTH, GEO_NAPHATH,
    GEO_NAPHATH__DOR, GEO_NAPHISH, GEO_NAPHOTH__DOR, GEO_NAZARETH, GEO_NEAH,
    GEO_NEAPOLIS, GEO_NEBAIOTH, GEO_NEBALLAT, GEO_NEBO, GEO_NEGEB,
    GEO_NEIEL, GEO_NEPHTOAH, GEO_NETAIM, GEO_NETOPHAH, GEO_NEZIB,
    GEO_NIBSHAN, GEO_NICOPOLIS, GEO_NILE, GEO_NIMRAH, GEO_NIMRIM,
    GEO_NIMROD, GEO_NINEVEH, GEO_NOB, GEO_NOBAH, GEO_NODAB,
    GEO_NOPHAH, GEO_OBOTH, GEO_OLIVET, GEO_ON, GEO_ONO,
    GEO_OPHEL, GEO_OPHIR, GEO_OPHNI, GEO_OPHRAH, GEO_PADDAN,
    GEO_PADDAN__ARAM, GEO_PAI, GEO_PAMPHYLIA, GEO_PAPHOS, GEO_PARAH,
    GEO_PARAN, GEO_PAS__DAMMIM, GEO_PATARA, GEO_PATHROS, GEO_PATMOS,
    GEO_PAU, GEO_PEKOD, GEO_PELUSIUM, GEO_PENIEL, GEO_PENUEL,
    GEO_PEOR, GEO_PEREZ__UZZA, GEO_PERGA, GEO_PERGAMUM, GEO_PERSIA,
    GEO_PETHOR, GEO_PHARPAR, GEO_PHILADELPHIA, GEO_PHILIPPI, GEO_PHILISTIA,
    GEO_PHOENICIA, GEO_PHOENIX, GEO_PHRYGIA, GEO_PI__BESETH, GEO_PIRATHON,
    GEO_PISGAH, GEO_PISIDIA, GEO_PITHOM, GEO_PONTUS, GEO_POOL_OF_SHELAH,
    GEO_PTOLEMAIS, GEO_PUL, GEO_PUNON, GEO_PUTEOLI, GEO_RAAMSES,
    GEO_RABBAH, GEO_RABBITH, GEO_RACAL, GEO_RAHAB, GEO_RAKKATH,
    GEO_RAKKON, GEO_RAMAH, GEO_RAMATH__LEHI, GEO_RAMATH__MIZPEH, GEO_RAMATHAIM__ZOPHIM,
    GEO_RAMESES, GEO_RAMOTH, GEO_RAMOTH__GILEAD, GEO_RED_SEA, GEO_REHOB,
    GEO_REHOBOTH, GEO_REHOBOTH__IR, GEO_REKEM, GEO_REMETH, GEO_REPHAIM,
    GEO_REPHIDIM, GEO_RESEN, GEO_REZEPH, GEO_RHEGIUM, GEO_RHODES,
    GEO_RIBLAH, GEO_RIMMON, GEO_RIMMON__PEREZ, GEO_RIMMONO, GEO_RISSAH,
    GEO_RITHMAH, GEO_ROME, GEO_SALAMIS, GEO_SALECAH, GEO_SALEM,
    GEO_SALIM, GEO_SALMONE, GEO_SALT_SEA, GEO_SAMARIA, GEO_SAMOS,
    GEO_SAMOTHRACE, GEO_SANSANNAH, GEO_SARDIS, GEO_SARID, GEO_SEA_OF_CHINNERETH,
    GEO_SEA_OF_CHINNEROTH, GEO_SEA_OF_EGYPT, GEO_SEA_OF_GALILEE, GEO_SEA_OF_JAZER, GEO_SEA_OF_THE_ARABAH,
    GEO_SEA_OF_THE_PHILISTINES, GEO_SEA_OF_TIBERIAS, GEO_SEBA, GEO_SEBAM, GEO_SECACAH,
    GEO_SECU, GEO_SEIR, GEO_SEIRAH, GEO_SELA, GEO_SELEUCIA,
    GEO_SENEH, GEO_SENIR, GEO_SEPHAR, GEO_SEPHARAD, GEO_SHAALABBIN,
    GEO_SHAALBIM, GEO_SHAALIM, GEO_SHAARAIM, GEO_SHAHAZUMAH, GEO_SHALISHAH,
    GEO_SHALLECHETH, GEO_SHAMIR, GEO_SHAPHIR, GEO_SHARON, GEO_SHARUHEN,
    GEO_SHAVEH__KIRIATHAIM, GEO_SHEBA, GEO_SHEBARIM, GEO_SHECHEM, GEO_SHEMA,
    GEO_SHEN, GEO_SHEPHAM, GEO_SHEPHELAH, GEO_SHIBAH, GEO_SHIKKERON,
    GEO_SHILHIM, GEO_SHILOAH, GEO_SHILOH, GEO_SHIMRON, GEO_SHIMRON__MERON,
    GEO_SHINAR, GEO_SHION, GEO_SHITTIM, GEO_SHOA, GEO_SHUAL,
    GEO_SHUNEM, GEO_SHUR, GEO_SIBMAH, GEO_SIBRAIM, GEO_SIDON,
    GEO_SILLA, GEO_SILOAM, GEO_SIN, GEO_SINAI, GEO_SIPHMOTH,
    GEO_SIRAH, GEO_SIRION, GEO_SITNAH, GEO_SMYRNA, GEO_SOCO,
    GEO_SOCOH, GEO_SODOM, GEO_SPAIN, GEO_SUCCOTH, GEO_SUPH,
    GEO_SUR, GEO_SUSA, GEO_SYCHAR, GEO_SYENE, GEO_SYRACUSE,
    GEO_SYRIA, GEO_SYRTIS, GEO_TAANACH, GEO_TAANATH__SHILOH, GEO_TABBATH,
    GEO_TABERAH, GEO_TABOR, GEO_TADMOR, GEO_TAHATH, GEO_TAHPANHES,
    GEO_TAMAR, GEO_TAPPUAH, GEO_TARALAH, GEO_TARSHISH, GEO_TARSUS,
    GEO_TEHAPHNEHES, GEO_TEKOA, GEO_TEL__HARSHA, GEO_TEL__MELAH, GEO_TELAIM,
    GEO_TELASSAR, GEO_TELEM, GEO_TEMA, GEO_TEMAN, GEO_TERAH,
    GEO_THYATIRA, GEO_TIBERIAS, GEO_TIBHATH, GEO_TIGRIS, GEO_TIMNAH,
    GEO_TIMNATH__HERES, GEO_TIMNATH__SERAH, GEO_TIPHSAH, GEO_TIRZAH, GEO_TISHBE,
    GEO_TOB, GEO_TOCHEN, GEO_TOLAD, GEO_TOPHEL, GEO_TOPHETH,
    GEO_TRACHONITIS, GEO_TROAS, GEO_TUBAL, GEO_TYRE, GEO_ULAI,
    GEO_UMMAH, GEO_UPHAZ, GEO_UPPER_BETH__HORON, GEO_UR, GEO_UZ,
    GEO_UZAL, GEO_UZZEN__SHEERAH, GEO_VALE_OF_SUCCOTH, GEO_VALLEY_OF_ACHOR, GEO_VALLEY_OF_AIJALON,
    GEO_VALLEY_OF_AVEN, GEO_VALLEY_OF_BERACAH, GEO_VALLEY_OF_ELAH, GEO_VALLEY_OF_ESHCOL, GEO_VALLEY_OF_GERAR,
    GEO_VALLEY_OF_GIBEON, GEO_VALLEY_OF_HAMON__GOG, GEO_VALLEY_OF_HINNOM, GEO_VALLEY_OF_IPHTAHEL, GEO_VALLEY_OF_JEHOSHAPHAT,
    GEO_VALLEY_OF_JERICHO, GEO_VALLEY_OF_JEZREEL, GEO_VALLEY_OF_LEBANON, GEO_VALLEY_OF_MIZPEH, GEO_VALLEY_OF_REPHAIM,
    GEO_VALLEY_OF_SALT, GEO_VALLEY_OF_SHAVEH, GEO_VALLEY_OF_SHITTIM, GEO_VALLEY_OF_SIDDIM, GEO_VALLEY_OF_SLAUGHTER,
    GEO_VALLEY_OF_SOREK, GEO_VALLEY_OF_SUCCOTH, GEO_VALLEY_OF_THE_ARNON, GEO_VALLEY_OF_THE_SON_OF_HINNOM, GEO_VALLEY_OF_THE_TRAVELERS,
    GEO_VALLEY_OF_ZEBOIM, GEO_VALLEY_OF_ZEPHATHAH, GEO_VALLEY_OF_ZERED, GEO_WAHEB, GEO_WAY_OF_HOLINESS,
    GEO_YIRON, GEO_ZAANAN, GEO_ZAANANNIM, GEO_ZAIR, GEO_ZALMON,
    GEO_ZALMONAH, GEO_ZANOAH, GEO_ZAPHON, GEO_ZAREPHATH, GEO_ZARETHAN,
    GEO_ZEBOIIM, GEO_ZEBOIM, GEO_ZEDAD, GEO_ZELA, GEO_ZELZAH,
    GEO_ZEMARAIM, GEO_ZENAN, GEO_ZEPHATH, GEO_ZER, GEO_ZERED,
    GEO_ZEREDAH, GEO_ZERETH__SHAHAR, GEO_ZIDDIM, GEO_ZIKLAG, GEO_ZIN,
    GEO_ZION, GEO_ZIOR, GEO_ZIPH, GEO_ZIPHRON, GEO_ZIZ,
    GEO_ZOAN, GEO_ZOAR, GEO_ZOBAH, GEO_ZOBAH__HAMATH, GEO_ZOPHIM,
    GEO_ZORAH, GEO_ZUPH,
    N_GEO_LOCATIONS
};

class SOWERBASEEXP SwGeo
{
public:
    static swUI32 FindByName(const char * name);
    static void GetMapLocation(swUI32 id, const SwGeoConversionData & cd, SwPoint & point);
    static swUI32 IdentifyLocation(const SwPoint & position, const SwGeoConversionData & cd);
    static void CalculatePosition(const SwGeoConversionData & cd, const SwGeoCoordinates & coords, SwPoint & point);
    static void CalculatePositionPoint(const SwGeoConversionData & cd, SwGeoCoordinates & coords, const SwPoint & point);
    static const SwGeoData & GetData(swUI32 id);
    static bool IsLocationValid(swUI32 location, SwGeoConversionData & cd);
    static void FillCtrl(wxChoice * choice);
    static void FillCtrl(wxListCtrl * listCtrl);
};

#endif // GEOLOCATION_H