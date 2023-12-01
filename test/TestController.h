//
//  TestController.h
//  tsf-tests
//
//  Created by Devine, Cameron - Xylem on 2/22/22.
//

#ifndef TestController_h
#define TestController_h

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"
#include <sstream>
#include OATPP_CODEGEN_BEGIN(DTO)

/**
 *  Data Transfer Object. Object containing fields only.
 *  Used in API for serialization/deserialization and validation
 */
class MyDto : public oatpp::DTO {
  
  DTO_INIT(MyDto, DTO)
  
  DTO_FIELD(Int32, statusCode);
  DTO_FIELD(String, message);
  
};

class ResultsDto : public oatpp::DTO {
  DTO_INIT(ResultsDto, DTO)
  
  DTO_FIELD(Int32, statusCode);
  DTO_FIELD(String, results);
};

#include OATPP_CODEGEN_END(DTO)

#include OATPP_CODEGEN_BEGIN(ApiController) ///Begin Codegen

/**
 * Sample Api Controller.
 */
class TestController : public oatpp::web::server::api::ApiController {
public:
  /**
   * Constructor with object mapper.
   * @param objectMapper - default object mapper used to serialize/deserialize DTOs.
   */
  TestController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
    : oatpp::web::server::api::ApiController(objectMapper)
  {
    setDefaultAuthorizationHandler(std::make_shared<oatpp::web::server::handler::BasicAuthorizationHandler>("my-realm"));
  }
public:
  
  ENDPOINT("GET", "/", root) {
    auto dto = MyDto::createShared();
    dto->statusCode = 200;
    dto->message = "Hello World!";
    return createDtoResponse(Status::CODE_200, dto);
  }
  
  ENDPOINT("GET", "/query", query, QUERIES(QueryParams, queryParams)) {
    //OATPP_ASSERT_HTTP(authObject->userId == "USER" && authObject->password == "PASS", Status::CODE_401, "Unauthorized");
    
    //Get the query parameter for basic testing
    std::string q;
    for(auto& param : queryParams.getAll()) {
      std::string first(param.first.std_str());
      std::string second(param.second.std_str());
      if(first.compare("q") == 0){
        q = second;
      }
    }
    String results;
    //Build example responses for certain queries
    if(q.compare("SHOW%20MEASUREMENTS%20LIMIT%201") == 0){
      results = "{\"results\":[{\"statement_id\":0,\"series\":[{\"name\":\"measurements\",\"columns\":[\"name\"],\"values\":[[\"Cluster1.WTR_CrkerSprgs_PRV_DisPres_P\"]]}]}]}";
    } else if(q.compare("show%20series") == 0 ){
      results = "{\"results\":[{\"statement_id\":0,\"series\":[{\"columns\":[\"key\"],\"values\":[[\"Cluster1.WTR_CrkerSprgs_PRV_DisPres_P,units=psi\"],[\"Cluster1.WTR_DryCreekRd_PRV_DisPres_P,units=psi\"],[\"Cluster1.WTR_DryForkRd_PRV_DisPres_P,units=psi\"],[\"Cluster1.WTR_EatonCrkRd_PRV_DisPres_P,units=psi\"],[\"concentration,tag=Cluster1.WTR_38thAve_WPS_CL2Res_P,units=mg/L\"],[\"concentration,tag=Cluster1.WTR_8thAve_CHM_CL2ResHach_P,units=mg/L\"],[\"concentration,tag=Cluster1.WTR_8thAve_CHM_CL2ResProm_P,units=mg/L\"],[\"concentration,tag=Cluster1.WTR_Airport_WPS_CL2Res_P,units=mg/L\"],[\"concentration,tag=Cluster1.WTR_BatteryLn_WPS_CL2Res_P,units=mg/L\"],[\"concentration,tag=Cluster1.WTR_BenAllen_RES_CL2Res_P,units=mg/L\"],[\"concentration,tag=Cluster1.WTR_BkChBsPrk_WPS_CL2Res_P,units=mg/L\"],[\"concentration,tag=Cluster1.WTR_BkChPk_WPS_CL2Res_P,units=mg/L\"],[\"concentration,tag=Cluster1.WTR_BluBeryHil_WPS_CL2Res_P,units=mg/L\"],[\"concentration,tag=Cluster1.WTR_Bonnafield_WPS_CL2Res_P,units=mg/L\"],[\"concentration,tag=Cluster1.WTR_Bordeaux_WPS_CL2Res_P,units=mg/L\"],[\"concentration,tag=Cluster1.WTR_BrntHghlnd_WPS_CL2Res_P,units=mg/L\"],[\"concentration,tag=Cluster1.WTR_Brookmont_WPS_CL2Res_P,units=mg/L\"],[\"concentration,tag=Cluster1.WTR_BullRun_RES_CL2Res_P,units=mg/L\"],[\"concentration,tag=Cluster1.WTR_CaneRidge_RES_CL2Res_P,units=mg/L\"],[\"concentration,tag=Cluster1.WTR_CentFarms_WPS_CL2Res_P,units=mg/L\"],[\"concentration,tag=Cluster1.WTR_ClfdlKnbhl_WPS_CL2Res_P,units=mg/L\"],[\"concentration,tag=Cluster1.WTR_EstesRd_WPS_CL2Res_P,units=mg/L\"],[\"concentration,tag=Cluster1.WTR_Fairmd_WPS_CL2Res_P,units=mg/L\"],[\"concentration,tag=Cluster1.WTR_GenelleDr_WPS_CL2Res_P,units=mg/L\"],[\"concentration,tag=Cluster1.WTR_GranyWhite_RES_CL2Res_P,units=mg/L\"],[\"concentration,tag=Cluster1.WTR_GranyWhite_WPS_CL2Res_P,units=mg/L\"],[\"concentration,tag=Cluster1.WTR_HardingPl_WPS_CL2Res_P,units=mg/L\"],[\"concentration,tag=Cluster1.WTR_HarpthTrce_WPS_CL2Res_P,units=mg/L\"],[\"concentration,tag=Cluster1.WTR_Hillview_WPS_CL2Res_P,units=mg/L\"],[\"concentration,tag=Cluster1.WTR_Hillwood_WPS_CL2Res_P,units=mg/L\"],[\"concentration,tag=Cluster1.WTR_HilsborPrk_RES_CL2Res_P,units=mg/L\"],[\"concentration,tag=Cluster1.WTR_HilwoodPrk_WPS_CL2Res_P,units=mg/L\"],[\"concentration,tag=Cluster1.WTR_HndRn_WPS_CL2Res_P,units=mg/L\"],[\"concentration,tag=Cluster1.WTR_HuntCanRdg_WPS_CR_CL2Res_P,units=mg/L\"],[\"concentration,tag=Cluster1.WTR_HuntCanRdg_WPS_HR_CL2Res_P,units=mg/L\"],[\"concentration,tag=Cluster1.WTR_IntrchgCty_RES_CL2Res_P,units=mg/L\"],[\"concentration,tag=Cluster1.WTR_JclynHolow_WPS_CL2Res_P,units=mg/L\"],[\"concentration,tag=Cluster1.WTR_Joelton_RES_CL2Res_P,units=mg/L\"],[\"concentration,tag=Cluster1.WTR_Kinhawk_RES_CL2Res_P,units=mg/L\"],[\"concentration,tag=Cluster1.WTR_KrHaringtn_WPS_CL2Res_P,units=mg/L\"],[\"concentration,tag=Cluster1.WTR_LaurelRidg_WPS_CL2Res_P,units=mg/L\"],[\"concentration,tag=Cluster1.WTR_LoveCircle_WPS_CL2Res_P,units=mg/L\"],[\"concentration,tag=Cluster1.WTR_MillsRd_WPS_CL2Res_P,units=mg/L\"],[\"concentration,tag=Cluster1.WTR_NrthmbrLnd_WPS_CL2Res_P,units=mg/L\"],[\"concentration,tag=Cluster1.WTR_Oakhill_WPS_CL2Res_P,units=mg/L\"],[\"concentration,tag=Cluster1.WTR_Oakwood_WPS_CL2Res_P,units=mg/L\"],[\"concentration,tag=Cluster1.WTR_Ocala_RES_CL2Res_P,units=mg/L\"],[\"concentration,tag=Cluster1.WTR_OldHickory_RES_CL2Res_P,units=mg/L\"],[\"concentration,tag=Cluster1.WTR_OldHickory_WPS_CL2Res_P,units=mg/L\"],[\"concentration,tag=Cluster1.WTR_Omohundro_WPS_CL2ResEast_P,units=mg/L\"],[\"concentration,tag=Cluster1.WTR_Omohundro_WPS_CL2ResWest_P,units=mg/L\"],[\"concentration,tag=Cluster1.WTR_Otterwood_WPS_CL2Res_P,units=mg/L\"],[\"concentration,tag=Cluster1.WTR_PorterRd_WPS_CL2Res_P,units=mg/L\"],[\"concentration,tag=Cluster1.WTR_PowellAve_WPS_CL2Res_P,units=mg/L\"],[\"concentration,tag=Cluster1.WTR_RiceRoad_WPS_CL2Res_P,units=mg/L\"],[\"concentration,tag=Cluster1.WTR_RollFork_WPS_CL2Res_P,units=mg/L\"],[\"concentration,tag=Cluster1.WTR_Rxborough2_RES_CL2Res_P,units=mg/L\"],[\"concentration,tag=Cluster1.WTR_Rxborough_WPS_CL2Res_P,units=mg/L\"],[\"concentration,tag=Cluster1.WTR_Shepardwod_WPS_CL2Res_P,units=mg/L\"],[\"concentration,tag=Cluster1.WTR_SherwdFrst_WPS_CL2Res_P,units=mg/L\"],[\"concentration,tag=Cluster1.WTR_Southerland_WPS_CL2Res_P,units=mg/L\"],[\"concentration,tag=Cluster1.WTR_Stanford_WPS_CL2Res_P,units=mg/L\"],[\"concentration,tag=Cluster1.WTR_SwissAve_RES_CL2Res_P,units=mg/L\"],[\"concentration,tag=Cluster1.WTR_TmpsonLane_WPS_CL2Res_P,units=mg/L\"],[\"concentration,tag=Cluster1.WTR_Treemont_WPS_CL2Res_P,units=mg/L\"],[\"concentration,tag=Cluster1.WTR_TrntyHlApt_WPS_CL2Res_P,units=mg/L\"],[\"concentration,tag=Cluster1.WTR_TyneValEst_WPS_CL2Res_P,units=mg/L\"],[\"concentration,tag=Cluster1.WTR_UnionHill_WPS_CL2Res_P,units=mg/L\"],[\"concentration,tag=Cluster1.WTR_Villacrest_WPS_CL2Res_P,units=mg/L\"],[\"concentration,tag=Cluster1.WTR_VirginaAve_WPS_CL2Res_P,units=mg/L\"],[\"concentration,tag=Cluster1.WTR_WarnerPark_WPS_CL2Res_P,units=mg/L\"],[\"concentration,tag=Cluster1.WTR_WhitesCrk_WPS_CL2Res_P,units=mg/L\"],[\"concentration,tag=Cluster1.WTR_WstMeadEst_WPS_CL2Res_P,units=mg/L\"],[\"concentration,tag=Cluster1.WTR_WstMeadFrm_WPS_CL2Res_P,units=mg/L\"],[\"concentration,tag=Cluster1.WTR_WstMeadHls_WPS_CL2Res_P,units=mg/L\"],[\"concentration,tag=Cluster1.WTR_WstMeadPrk_WPS_CL2Res_P,units=mg/L\"],[\"concentration,tag=Cluster1.WTR_WvrlyBlmnt_WPS_CL2Res_P,units=mg/L\"],[\"flow,tag=Cluster1.WTR_38thAve_WPS_Flw_P,units=gpm\"],[\"flow,tag=Cluster1.WTR_Airport_PRV_Flw_P,units=gpm\"],[\"flow,tag=Cluster1.WTR_Airport_WPS_Flw_P,units=gpm\"],[\"flow,tag=Cluster1.WTR_BatteryLn_HardingPl_WPS_FlwSum_P,units=gpm\"],[\"flow,tag=Cluster1.WTR_BatteryLn_WPS_Flw_P,units=gpm\"],[\"flow,tag=Cluster1.WTR_BkChBsPrk_WPS_FlwSum_P,units=gpm\"],[\"flow,tag=Cluster1.WTR_BkChBsPrk_WPS_Flw_P,units=gpm\"],[\"flow,tag=Cluster1.WTR_BkChPk_WPS_Flw_P,units=gpm\"],[\"flow,tag=Cluster1.WTR_BluBeryHil_WPS_Flw_P,units=gpm\"],[\"flow,tag=Cluster1.WTR_Bonnafield_WPS_Flw_P,units=gpm\"],[\"flow,tag=Cluster1.WTR_Bordeaux_WPS_Flw_P,units=gpm\"],[\"flow,tag=Cluster1.WTR_Brentwood_FLW_Flw_P,units=gpm\"],[\"flow,tag=Cluster1.WTR_BrntHghlnd_RES_DmdFlw_P,units=gpm\"],[\"flow,tag=Cluster1.WTR_BrntHghlnd_WPS_Flw_P,units=gpm\"],[\"flow,tag=Cluster1.WTR_Brookmont_WPS_Flw_P,units=gpm\"],[\"flow,tag=Cluster1.WTR_CaneRidge_RES_DmdFlw_P,units=gpm\"],[\"flow,tag=Cluster1.WTR_CentFarms_WPS_Flw_P,units=gpm\"],[\"flow,tag=Cluster1.WTR_ClfdlKnbhl_WPS_Flw_P,units=gpm\"],[\"flow,tag=Cluster1.WTR_EstesRd_WPS_Flw_P,units=gpm\"],[\"flow,tag=Cluster1.WTR_Fairmd_WPS_Flw_P,units=gpm\"],[\"flow,tag=Cluster1.WTR_GenelleDr_WPS_Flw_P,units=gpm\"],[\"flow,tag=Cluster1.WTR_GranyWhite_RES_DmdFlw_P,units=gpm\"],[\"flow,tag=Cluster1.WTR_GranyWhite_WPS_Flw_P,units=gpm\"],[\"flow,tag=Cluster1.WTR_HardingPl_WPS_Flw_P,units=gpm\"],[\"flow,tag=Cluster1.WTR_HarpthTrce_WPS_Flw_P,units=gpm\"],[\"flow,tag=Cluster1.WTR_Hillview_WPS_Flw_P,units=gpm\"],[\"flow,tag=Cluster1.WTR_Hillwood_WPS_FlwSum_P,units=gpm\"],[\"flow,tag=Cluster1.WTR_Hillwood_WPS_Flw_P,units=gpm\"],[\"flow,tag=Cluster1.WTR_HilwoodPrk_WPS_Flw_P,units=gpm\"],[\"flow,tag=Cluster1.WTR_HndRn_WPS_Flw_P,units=gpm\"],[\"flow,tag=Cluster1.WTR_HuntCanRdg_RES_DmdFlw_P,units=gpm\"],[\"flow,tag=Cluster1.WTR_HuntCanRdg_WPS_CR_Flw_P,units=gpm\"],[\"flow,tag=Cluster1.WTR_HuntCanRdg_WPS_FlwSum_P,units=gpm\"],[\"flow,tag=Cluster1.WTR_HuntCanRdg_WPS_HR_Flw_P,units=gpm\"],[\"flow,tag=Cluster1.WTR_JclynHolow_WPS_Flw_P,units=gpm\"],[\"flow,tag=Cluster1.WTR_KrHaringtn_WPS_FinFlw1_P,units=mgd\"],[\"flow,tag=Cluster1.WTR_KrHaringtn_WPS_FinFlw2_P,units=mgd\"],[\"flow,tag=Cluster1.WTR_KrHaringtn_WPS_Flw_P,units=mgd\"],[\"flow,tag=Cluster1.WTR_LaurelRidg_WPS_Flw_P,units=gpm\"],[\"flow,tag=Cluster1.WTR_LoveCircle_WPS_Flw_P,units=gpm\"],[\"flow,tag=Cluster1.WTR_MillsRd_WPS_Flw_P,units=gpm\"],[\"flow,tag=Cluster1.WTR_NrthmbrLnd_WPS_Flw_P,units=gpm\"],[\"flow,tag=Cluster1.WTR_Oakhill_WPS_Flw_P,units=gpm\"],[\"flow,tag=Cluster1.WTR_Oakwood_WPS_Flw_P,units=gpm\"],[\"flow,tag=Cluster1.WTR_OldHickory_WPS_Flw_P,units=gpm\"],[\"flow,tag=Cluster1.WTR_Oman_WPS_Flw_P,units=gpm\"],[\"flow,tag=Cluster1.WTR_Omohundro_WPS_BWFlw1_P,units=gpm\"],[\"flow,tag=Cluster1.WTR_Omohundro_WPS_FinFlw1_P,units=mgd\"],[\"flow,tag=Cluster1.WTR_Omohundro_WPS_FinFlw2_P,units=mgd\"],[\"flow,tag=Cluster1.WTR_Omohundro_WPS_Flw_P,units=mgd\"],[\"flow,tag=Cluster1.WTR_Otterwood_WPS_Flw_P,units=gpm\"],[\"flow,tag=Cluster1.WTR_PorterRd_WPS_Flw_P,units=gpm\"],[\"flow,tag=Cluster1.WTR_PowellAve_WPS_Flw_P,units=gpm\"],[\"flow,tag=Cluster1.WTR_RiceRoad_WPS_Flw_P,units=gpm\"],[\"flow,tag=Cluster1.WTR_RollFork_RES_DmdFlw_P,units=gpm\"],[\"flow,tag=Cluster1.WTR_RollFork_WPS_Flw_P,units=gpm\"],[\"flow,tag=Cluster1.WTR_Rxborough_WPS_Flw_P,units=gpm\"],[\"flow,tag=Cluster1.WTR_Shepardwod_WPS_Flw_P,units=gpm\"],[\"flow,tag=Cluster1.WTR_SherwdFrst_WPS_Flw_P,units=gpm\"],[\"flow,tag=Cluster1.WTR_Southerland_WPS_Flw_P,units=gpm\"],[\"flow,tag=Cluster1.WTR_Stanford_WPS_Flw_P,units=gpm\"],[\"flow,tag=Cluster1.WTR_ThorntonGrv_PRV_Flw_P,units=gpm\"],[\"flow,tag=Cluster1.WTR_TmpsonLane_EstesRd_WPS_FlwSum_P,units=gpm\"],[\"flow,tag=Cluster1.WTR_TmpsonLane_WPS_Flw_P,units=gpm\"],[\"flow,tag=Cluster1.WTR_Treemont_WPS_Flw_P,units=gpm\"],[\"flow,tag=Cluster1.WTR_TrntyHlApt_WPS_Flw_P,units=gpm\"],[\"flow,tag=Cluster1.WTR_TyneValEst_WPS_Flw_P,units=gpm\"],[\"flow,tag=Cluster1.WTR_UnionHill_WPS_Flw_P,units=gpm\"],[\"flow,tag=Cluster1.WTR_Villacrest_WPS_Flw_P,units=gpm\"],[\"flow,tag=Cluster1.WTR_VirginaAve_WPS_Flw_P,units=gpm\"],[\"flow,tag=Cluster1.WTR_WarnerPark_WPS_Flw_P,units=gpm\"],[\"flow,tag=Cluster1.WTR_WhitesCrk_WPS_Flw_P,units=gpm\"],[\"flow,tag=Cluster1.WTR_WstMeadEst_RES_DmdFlw_P,units=gpm\"],[\"flow,tag=Cluster1.WTR_WstMeadEst_WPS_Flw_P,units=gpm\"],[\"flow,tag=Cluster1.WTR_WstMeadFrm_WPS_Flw_P,units=gpm\"],[\"flow,tag=Cluster1.WTR_WstMeadHls_RES_DmdFlw_P,units=gpm\"],[\"flow,tag=Cluster1.WTR_WstMeadHls_WPS_Flw_P,units=gpm\"],[\"flow,tag=Cluster1.WTR_WstMeadPrk_WPS_Flw_P,units=gpm\"],[\"flow,tag=Cluster1.WTR_WvrlyBlmnt_WPS_Flw_P,units=gpm\"],[\"level,tag=Cluster1.WTR_38thAve_WPS_Res1Lvl_P,units=ft\"],[\"level,tag=Cluster1.WTR_8thAve_RES_Res1Lvl_P,units=ft\"],[\"level,tag=Cluster1.WTR_8thAve_RES_Res2Lvl_P,units=ft\"],[\"level,tag=Cluster1.WTR_BenAllen_RES_Res1Lvl_P,units=ft\"],[\"level,tag=Cluster1.WTR_BkChBsPrk_RES_Res1Lvl_P,units=ft\"],[\"level,tag=Cluster1.WTR_Bordeaux_RES_Res1Lvl_P,units=ft\"],[\"level,tag=Cluster1.WTR_BrntHghlnd_RES_Res1Lvl_P,units=ft\"],[\"level,tag=Cluster1.WTR_BullRun_RES_Res1Lvl_P,units=ft\"],[\"level,tag=Cluster1.WTR_CaneRidge_RES_Res1Lvl_P,units=ft\"],[\"level,tag=Cluster1.WTR_GranyWhite_RES_Res1Lvl_P,units=ft\"],[\"level,tag=Cluster1.WTR_HarpthTrce_WPS_WP_Res1Lvl_P,units=ft\"],[\"level,tag=Cluster1.WTR_HilsborPrk_RES_Res1Lvl_P,units=ft\"],[\"level,tag=Cluster1.WTR_IntrchgCty_RES_Res1Lvl_P,units=ft\"],[\"level,tag=Cluster1.WTR_Joelton_RES_Res1Lvl_P,units=ft\"],[\"level,tag=Cluster1.WTR_Kinhawk_RES_Res1Lvl_P,units=ft\"],[\"level,tag=Cluster1.WTR_KrHaringtn_WPS_ClrWl1Lvl_P,units=ft\"],[\"level,tag=Cluster1.WTR_KrHaringtn_WPS_ClrWl2Lvl_P,units=ft\"],[\"level,tag=Cluster1.WTR_LaurelRidg_WPS_TVE_Res1Lvl_P,units=ft\"],[\"level,tag=Cluster1.WTR_LoveCircle_RES_Res1Lvl_P,units=ft\"],[\"level,tag=Cluster1.WTR_MillsRd_RES_Res1Lvl_P,units=ft\"],[\"level,tag=Cluster1.WTR_NrthmbrLnd_WPS_HGP_Res1Lvl_P,units=ft\"],[\"level,tag=Cluster1.WTR_Oakhill2_RES_Res1Lvl_P,units=ft\"],[\"level,tag=Cluster1.WTR_Oakhill_WPS_Res1Lvl_P,units=ft\"],[\"level,tag=Cluster1.WTR_Ocala_RES_Res1Lvl_P,units=ft\"],[\"level,tag=Cluster1.WTR_OldHickory_RES_Res1Lvl_P,units=ft\"],[\"level,tag=Cluster1.WTR_Omohundro_WPS_BWRes1Lvl_P,units=ft\"],[\"level,tag=Cluster1.WTR_Omohundro_WPS_ClrWl1Lvl_P,units=ft\"],[\"level,tag=Cluster1.WTR_Omohundro_WPS_ClrWl2Lvl_P,units=ft\"],[\"level,tag=Cluster1.WTR_Omohundro_WPS_ClrWl3Lvl_P,units=ft\"],[\"level,tag=Cluster1.WTR_Omohundro_WPS_ClrWl4Lvl_P,units=ft\"],[\"level,tag=Cluster1.WTR_RiceRoad_WPS_Res1Lvl_P,units=ft\"],[\"level,tag=Cluster1.WTR_RollFork_RES_Res1Lvl_P,units=ft\"],[\"level,tag=Cluster1.WTR_Rxborough2_RES_Res1Lvl_P,units=ft\"],[\"level,tag=Cluster1.WTR_SwissAve_RES_Res1Lvl_P,units=ft\"],[\"level,tag=Cluster1.WTR_TrinityLne_RES_Res1Lvl_P,units=ft\"],[\"level,tag=Cluster1.WTR_UnionHill_WPS_Res1Lvl_P,units=ft\"],[\"level,tag=Cluster1.WTR_WhitesCrk_RES_Res1Lvl_P,units=ft\"],[\"level,tag=Cluster1.WTR_WstMeadEst_RES_Res1Lvl_P,units=ft\"],[\"level,tag=Cluster1.WTR_WstMeadHls_RES_Res1Lvl_P,units=ft\"],[\"level,tag=Cluster1.WTR_WstMeadPrk_RES_Res1Lvl_P,units=ft\"],[\"ph,tag=Cluster1.WTR_PowellAve_WPS_H2OPH_P,units=dimensionless\"],[\"position,tag=Cluster1.WTR_8thAve_RES_EfVPos_P,units=%\"],[\"position,tag=Cluster1.WTR_8thAve_RES_IVPos_P,units=%\"],[\"position,tag=Cluster1.WTR_Oakhill_WPS_VPos_P,units=%\"],[\"pressure,tag=Cluster1.WTR_38thAve_WPS_DisPres_P,units=psi\"],[\"pressure,tag=Cluster1.WTR_38thAve_WPS_MainPres_P,units=psi\"],[\"pressure,tag=Cluster1.WTR_38thAve_WPS_SucPres_P,units=psi\"],[\"pressure,tag=Cluster1.WTR_Airport_PRV_DisPres_P,units=psi\"],[\"pressure,tag=Cluster1.WTR_Airport_PRV_InPres_P,units=psi\"],[\"pressure,tag=Cluster1.WTR_Airport_WPS_DisPres_P,units=psi\"],[\"pressure,tag=Cluster1.WTR_Airport_WPS_SucPres_P,units=psi\"],[\"pressure,tag=Cluster1.WTR_AmalieDr_PRV_DisPres_P,units=psi\"],[\"pressure,tag=Cluster1.WTR_BarnesRd_PRV_DisPres_P,units=psi\"],[\"pressure,tag=Cluster1.WTR_BatteryLn_WPS_DisPres_P,units=psi\"],[\"pressure,tag=Cluster1.WTR_BatteryLn_WPS_SucPres_P,units=psi\"],[\"pressure,tag=Cluster1.WTR_BellRd_PRV_DisPres_P,units=psi\"],[\"pressure,tag=Cluster1.WTR_BenAllen_RES_MainPres_P,units=psi\"],[\"pressure,tag=Cluster1.WTR_BkChBsPrk_WPS_DisPres_P,units=psi\"],[\"pressure,tag=Cluster1.WTR_BkChBsPrk_WPS_SucPres_P,units=psi\"],[\"pressure,tag=Cluster1.WTR_BkChPk_WPS_DisPres_P,units=psi\"],[\"pressure,tag=Cluster1.WTR_BkChPk_WPS_SucPres_P,units=psi\"],[\"pressure,tag=Cluster1.WTR_BluBeryHil_WPS_DisPres_P,units=psi\"],[\"pressure,tag=Cluster1.WTR_BluBeryHil_WPS_SucPres_P,units=psi\"],[\"pressure,tag=Cluster1.WTR_Bonnafield_WPS_DisPres_P,units=psi\"],[\"pressure,tag=Cluster1.WTR_Bonnafield_WPS_SucPres_P,units=psi\"],[\"pressure,tag=Cluster1.WTR_Bordeaux_WPS_DisPres_P,units=psi\"],[\"pressure,tag=Cluster1.WTR_Bordeaux_WPS_SucPres_P,units=psi\"],[\"pressure,tag=Cluster1.WTR_BriarvleRd_PRV_DisPres_P,units=psi\"],[\"pressure,tag=Cluster1.WTR_BriarvleRd_PRV_InPres_P,units=psi\"],[\"pressure,tag=Cluster1.WTR_BrileyPkwy_PRV_DisPres_P,units=psi\"],[\"pressure,tag=Cluster1.WTR_BrntHghlnd_WPS_DisPres_P,units=psi\"],[\"pressure,tag=Cluster1.WTR_BrntHghlnd_WPS_SucPres_P,units=psi\"],[\"pressure,tag=Cluster1.WTR_BrntwoodSq_PRV_DisPres_P,units=psi\"],[\"pressure,tag=Cluster1.WTR_Brookmont_WPS_DisPres_P,units=psi\"],[\"pressure,tag=Cluster1.WTR_Brookmont_WPS_SucPres_P,units=psi\"],[\"pressure,tag=Cluster1.WTR_BullRun_RES_MainPres_P,units=psi\"],[\"pressure,tag=Cluster1.WTR_CampbellRd_PRV_DisPres_P,units=psi\"],[\"pressure,tag=Cluster1.WTR_CaneRidge_PRV_DisPres_P,units=psi\"],[\"pressure,tag=Cluster1.WTR_CaneRidge_PRV_InPres_P,units=psi\"],[\"pressure,tag=Cluster1.WTR_CentFarms_WPS_DisPres_P,units=psi\"],[\"pressure,tag=Cluster1.WTR_CentFarms_WPS_SucPres_P,units=psi\"],[\"pressure,tag=Cluster1.WTR_ChsapeakDr_PRV_DisPres_P,units=psi\"],[\"pressure,tag=Cluster1.WTR_ClfdlKnbhl_WPS_DisPres_P,units=psi\"],[\"pressure,tag=Cluster1.WTR_ClfdlKnbhl_WPS_SucPres_P,units=psi\"],[\"pressure,tag=Cluster1.WTR_CloverGlen_PRV_DisPres_P,units=psi\"],[\"pressure,tag=Cluster1.WTR_CloverGlen_PRV_InPres_P,units=psi\"],[\"pressure,tag=Cluster1.WTR_EstesRd_WPS_DisPres_P,units=psi\"],[\"pressure,tag=Cluster1.WTR_EstesRd_WPS_SucPres_P,units=psi\"],[\"pressure,tag=Cluster1.WTR_Fairmd_WPS_DisPres_P,units=psi\"],[\"pressure,tag=Cluster1.WTR_Fairmd_WPS_SucPres_P,units=psi\"],[\"pressure,tag=Cluster1.WTR_GenelleDr_WPS_DisPres_P,units=psi\"],[\"pressure,tag=Cluster1.WTR_GenelleDr_WPS_SucPres_P,units=psi\"],[\"pressure,tag=Cluster1.WTR_GranyWhite_RES_MainPres_P,units=psi\"],[\"pressure,tag=Cluster1.WTR_GranyWhite_WPS_DisPres_P,units=psi\"],[\"pressure,tag=Cluster1.WTR_GranyWhite_WPS_SucPres_P,units=psi\"],[\"pressure,tag=Cluster1.WTR_HardingPl_WPS_DisPres_P,units=psi\"],[\"pressure,tag=Cluster1.WTR_HardingPl_WPS_SucPres_P,units=psi\"],[\"pressure,tag=Cluster1.WTR_HarpthTrce_WPS_DisPres_P,units=psi\"],[\"pressure,tag=Cluster1.WTR_HarpthTrce_WPS_SucPres_P,units=psi\"],[\"pressure,tag=Cluster1.WTR_HearthtnLn_PRV_DisPres_P,units=psi\"],[\"pressure,tag=Cluster1.WTR_Hillview_WPS_DisPres_P,units=psi\"],[\"pressure,tag=Cluster1.WTR_Hillview_WPS_SucPres_P,units=psi\"],[\"pressure,tag=Cluster1.WTR_Hillwood_WPS_DisPres_P,units=psi\"],[\"pressure,tag=Cluster1.WTR_Hillwood_WPS_SucPres_P,units=psi\"],[\"pressure,tag=Cluster1.WTR_HilsborPrk_RES_MainPres_P,units=psi\"],[\"speed,tag=Cluster1.WTR_Hillwood_WPS_Pmp_SPEED,units=%\"],[\"speed,tag=Cluster1.WTR_HilwoodPrk_WPS_Pmp_SPEED,units=%\"],[\"speed,tag=Cluster1.WTR_HndRn_WPS_Pmp_SPEED,units=%\"],[\"speed,tag=Cluster1.WTR_HuntCanRdg_WPS_CR_Pmp_SPEED,units=%\"],[\"speed,tag=Cluster1.WTR_HuntCanRdg_WPS_HR_Pmp_SPEED,units=%\"],[\"speed,tag=Cluster1.WTR_JclynHolow_WPS_Pmp_SPEED,units=%\"],[\"speed,tag=Cluster1.WTR_KrHaringtn_WPS_Pmp1HS_Speed,units=%\"],[\"speed,tag=Cluster1.WTR_KrHaringtn_WPS_Pmp2HS_Speed,units=%\"],[\"speed,tag=Cluster1.WTR_KrHaringtn_WPS_Pmp3HS_Speed,units=%\"],[\"speed,tag=Cluster1.WTR_KrHaringtn_WPS_Pmp4HS_Speed,units=%\"],[\"speed,tag=Cluster1.WTR_KrHaringtn_WPS_Pmp_SPEED,units=%\"],[\"speed,tag=Cluster1.WTR_LaurelRidg_WPS_Pmp_SPEED,units=%\"],[\"speed,tag=Cluster1.WTR_LoveCircle_WPS_Pmp_SPEED,units=%\"],[\"speed,tag=Cluster1.WTR_MillsRd_WPS_Pmp_SPEED,units=%\"],[\"speed,tag=Cluster1.WTR_NrthmbrLnd_WPS_Pmp_SPEED,units=%\"],[\"speed,tag=Cluster1.WTR_Oakhill_WPS_Pmp_SPEED,units=%\"],[\"speed,tag=Cluster1.WTR_Oakwood_WPS_Pmp_SPEED,units=%\"],[\"speed,tag=Cluster1.WTR_OldHickory_WPS_Pmp_SPEED,units=%\"],[\"speed,tag=Cluster1.WTR_WvrlyBlmnt_WPS_Pmp_SPEED,units=%\"],[\"status,tag=Cluster1.WTR_38thAve_WPS_Gen_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_38thAve_WPS_Pmp1_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_38thAve_WPS_Pmp2_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_38thAve_WPS_Pmp3_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_38thAve_WPS_Pmp4_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_38thAve_WPS_RES_V1_OP,units=dimensionless\"],[\"status,tag=Cluster1.WTR_38thAve_WPS_RES_V1_STATVLV,units=dimensionless\"],[\"status,tag=Cluster1.WTR_8thAve_RES_EstCPmp_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_8thAve_RES_EstUPmp_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_Airport_WPS_Gen_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_Airport_WPS_Pmp1_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_Airport_WPS_Pmp2_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_Airport_WPS_Pmp3_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_Airport_WPS_Pmp4_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_Airport_WPS_SurgV_OP,units=dimensionless\"],[\"status,tag=Cluster1.WTR_AshlandCtyHw_VLV_V1_OP,units=dimensionless\"],[\"status,tag=Cluster1.WTR_AshlandCtyHw_VLV_V1_STATVLV,units=dimensionless\"],[\"status,tag=Cluster1.WTR_BatteryLn_WPS_Pmp1_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_BatteryLn_WPS_Pmp2_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_BatteryLn_WPS_Pmp3_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_BatteryLn_WPS_Pmp4_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_BenAllen_RES_V1_OP,units=dimensionless\"],[\"status,tag=Cluster1.WTR_BenAllen_RES_V1_STATVLV,units=dimensionless\"],[\"status,tag=Cluster1.WTR_BkChBsPrk_RES_V1_OP,units=dimensionless\"],[\"status,tag=Cluster1.WTR_BkChBsPrk_RES_V1_STATVLV,units=dimensionless\"],[\"status,tag=Cluster1.WTR_BkChBsPrk_WPS_Gen_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_BkChBsPrk_WPS_Pmp1_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_BkChBsPrk_WPS_Pmp2_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_BkChPk_WPS_Pmp1_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_BkChPk_WPS_Pmp2_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_BkChPk_WPS_Pmp3_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_BluBeryHil_WPS_Gen_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_BluBeryHil_WPS_Pmp1_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_BluBeryHil_WPS_Pmp2_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_Bonnafield_WPS_Pmp1_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_Bordeaux_RES_V1_OP,units=dimensionless\"],[\"status,tag=Cluster1.WTR_Bordeaux_RES_V1_STATVLV,units=dimensionless\"],[\"status,tag=Cluster1.WTR_Bordeaux_WPS_Pmp1_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_Bordeaux_WPS_Pmp2_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_Bordeaux_WPS_Pmp3_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_BrntHghlnd_RES_V1_OP,units=dimensionless\"],[\"status,tag=Cluster1.WTR_BrntHghlnd_RES_V1_STATVLV,units=dimensionless\"],[\"status,tag=Cluster1.WTR_BrntHghlnd_WPS_Pmp1_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_BrntHghlnd_WPS_Pmp2_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_Brookmont_WPS_Gen_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_Brookmont_WPS_Pmp1_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_Brookmont_WPS_Pmp2_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_Brookmont_WPS_Pmp3_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_BullRun_RES_V1_OP,units=dimensionless\"],[\"status,tag=Cluster1.WTR_BullRun_RES_V1_STATVLV,units=dimensionless\"],[\"status,tag=Cluster1.WTR_CaneRidge_RES_V1_OP,units=dimensionless\"],[\"status,tag=Cluster1.WTR_CaneRidge_RES_V1_STATVLV,units=dimensionless\"],[\"status,tag=Cluster1.WTR_CentFarms_WPS_Pmp1_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_CentFarms_WPS_Pmp2_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_CentFarms_WPS_Pmp3_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_CentFarms_WPS_Pmp4_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_ClfdlKnbhl_WPS_Gen_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_ClfdlKnbhl_WPS_Pmp1_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_ClfdlKnbhl_WPS_Pmp2_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_EstesRd_WPS_Pmp1_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_EstesRd_WPS_Pmp2_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_Fairmd_WPS_Gen_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_Fairmd_WPS_Pmp1_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_Fairmd_WPS_Pmp2_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_Fairmd_WPS_Pmp3_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_GenelleDr_WPS_Pmp1_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_GranyWhite_RES_V1_OP,units=dimensionless\"],[\"status,tag=Cluster1.WTR_GranyWhite_RES_V1_STATVLV,units=dimensionless\"],[\"status,tag=Cluster1.WTR_GranyWhite_WPS_Pmp1_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_GranyWhite_WPS_Pmp2_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_GranyWhite_WPS_Pmp3_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_GranyWhite_WPS_Pmp4_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_HardingPl_WPS_Pmp1_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_HardingPl_WPS_Pmp2_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_HardingPl_WPS_Pmp3_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_HarpthTrce_WPS_Gen_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_HarpthTrce_WPS_Pmp1_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_HarpthTrce_WPS_Pmp2_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_HarpthTrce_WPS_Pmp3_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_HarpthTrce_WPS_RES_V1_OP,units=dimensionless\"],[\"status,tag=Cluster1.WTR_HarpthTrce_WPS_RES_V1_STATVLV,units=dimensionless\"],[\"status,tag=Cluster1.WTR_HillsborRd_VLV_V1_OP,units=dimensionless\"],[\"status,tag=Cluster1.WTR_HillsborRd_VLV_V1_STATVLV,units=dimensionless\"],[\"status,tag=Cluster1.WTR_Hillview_WPS_Gen_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_Hillview_WPS_Pmp1_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_Hillview_WPS_Pmp2_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_Hillwood_WPS_Gen_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_Hillwood_WPS_Pmp1_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_Hillwood_WPS_Pmp2_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_Hillwood_WPS_Pmp3_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_HilsborPrk_RES_V1_OP,units=dimensionless\"],[\"status,tag=Cluster1.WTR_HilsborPrk_RES_V1_STATVLV,units=dimensionless\"],[\"status,tag=Cluster1.WTR_HilwoodPrk_WPS_Gen_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_HilwoodPrk_WPS_Pmp1_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_HilwoodPrk_WPS_Pmp2_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_HndRn_WPS_Gen_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_HndRn_WPS_Pmp1_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_HndRn_WPS_Pmp2_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_HuntCanRdg_WPS_CR_Pmp1_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_HuntCanRdg_WPS_CR_Pmp2_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_HuntCanRdg_WPS_Gen_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_HuntCanRdg_WPS_HR_Pmp1_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_Shepardwod_WPS_Pmp3_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_SherwdFrst_WPS_Pmp1_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_SherwdFrst_WPS_Pmp2_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_SherwdFrst_WPS_Pmp3_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_Southerland_WPS_Gen_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_Southerland_WPS_Pmp1_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_Southerland_WPS_Pmp2_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_Southerland_WPS_Pmp3_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_Stanford_WPS_Gen_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_Stanford_WPS_Pmp1_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_Stanford_WPS_Pmp2_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_SwissAve_RES_V1_OP,units=dimensionless\"],[\"status,tag=Cluster1.WTR_SwissAve_RES_V1_STATVLV,units=dimensionless\"],[\"status,tag=Cluster1.WTR_TmpsonLane_WPS_Pmp1_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_TmpsonLane_WPS_Pmp2_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_TmpsonLane_WPS_Pmp3_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_TmpsonLane_WPS_Pmp4_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_TmpsonLane_WPS_SurgeVlv_OP,units=dimensionless\"],[\"status,tag=Cluster1.WTR_Treemont_WPS_Gen_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_Treemont_WPS_Pmp1_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_Treemont_WPS_Pmp2_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_Treemont_WPS_Pmp3_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_TrinityLne_RES_V1_OP,units=dimensionless\"],[\"status,tag=Cluster1.WTR_TrinityLne_RES_V1_STATVLV,units=dimensionless\"],[\"status,tag=Cluster1.WTR_TrntyHlApt_WPS_Pmp1_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_TrntyHlApt_WPS_Pmp2_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_TyneValEst_WPS_Pmp1_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_TyneValEst_WPS_Pmp2_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_UnionHill_WPS_Gen_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_UnionHill_WPS_Pmp1_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_UnionHill_WPS_Pmp2_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_UnionHill_WPS_Pmp3_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_Villacrest_WPS_Pmp1_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_Villacrest_WPS_Pmp2_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_Villacrest_WPS_Pmp3_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_VirginaAve_WPS_Pmp1_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_VirginaAve_WPS_Pmp2_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_VirginaAve_WPS_Pmp3_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_WarnerPark_WPS_Pmp1_RUN,units=dimensionless\"],[\"status,tag=Cluster1.WTR_WarnerPark_WPS_Pmp2_RUN,units=dimensionless\"],[\"temperature,tag=Cluster1.WTR_PowellAve_WPS_H2OTEMP_P,units=farenheit\"]]}]}]}";

    }
    return createResponse(Status::CODE_200, results);
  }
  
};

#include OATPP_CODEGEN_END(ApiController) ///End Codegen

#endif /* TestController_h */
