package script.map_sm
{
   internal class StageUtil
   {
      
      public static const STAGE_ID_NAME_SUNAGAKURE:String = "sa11";
      
      public static const STAGE_ID_NAME_GOKAGE:String = "sa13a";
      
      public static const STAGE_ID_NAME_UCHIHA:String = "sa15a";
      
      public static const STAGE_ID_NAME_AMEGAKURE:String = "sa16";
      
      public static const STAGE_ID_NAME_SAMURAI:String = "sa17a";
      
      public static const STAGE_ID_NAME_SHIMAGAME_1:String = "sa34";
      
      public static const STAGE_ID_NAME_SHIMAGAME_2:String = "sa35a";
      
      public static const STAGE_ID_NAME_SHIMAGAME_3:String = "sa02b";
      
      public static const STAGE_ID_NAME_KUMOGAKURE:String = "sa36";
      
      public static const STAGE_ID_NAME_NARUTOOHASHI:String = "sa71a";
      
      public static const STAGE_ID_NAME_SHINOHASHI:String = "sd01d";
      
      public static const STAGE_ID_NAME_KONOHANOMORI:String = "sd03a";
      
      public static const STAGE_ID_NAME_OROCHIMARU:String = "sd07a";
      
      public static const STAGE_ID_NAME_KAZENOSABAKU:String = "sd08a";
      
      public static const STAGE_ID_NAME_UNRAIKYO:String = "sd16a";
      
      public static const STAGE_ID_NAME_SERVIVAL:String = "si00a";
      
      public static const STAGE_ID_NAME_SENKUTU:String = "si35a";
      
      public static const STAGE_ID_NAME_SYUMATU:String = "si51f";
      
      public static const STAGE_ID_NAME_SHINKONOHA:String = "sa70";
      
      public function StageUtil()
      {
         super();
      }
      
      public static function Check_SYUNSHIN_JumpStage(param1:String) : Boolean
      {
         var _loc2_:Boolean = false;
         if(param1.indexOf(STAGE_ID_NAME_AMEGAKURE) == -1 && param1.indexOf(STAGE_ID_NAME_SHINKONOHA) == -1 && param1.indexOf(STAGE_ID_NAME_SUNAGAKURE) == -1 && param1.indexOf(STAGE_ID_NAME_KUMOGAKURE) == -1 && param1.indexOf(STAGE_ID_NAME_SHIMAGAME_1) == -1 && param1.indexOf(STAGE_ID_NAME_SHIMAGAME_2) == -1 && param1.indexOf(STAGE_ID_NAME_SHIMAGAME_3) == -1)
         {
            _loc2_ = true;
         }
         return _loc2_;
      }
      
      public static function RenameStageMapName(param1:String) : String
      {
         var _loc2_:String = param1;
         if(param1.indexOf(STAGE_ID_NAME_SHIMAGAME_2) != -1 || param1.indexOf(STAGE_ID_NAME_SHIMAGAME_3) != -1)
         {
            _loc2_ = "map_sa34";
         }
         else if(param1.indexOf(STAGE_ID_NAME_SHINKONOHA) != -1)
         {
            _loc2_ = "map_sa70a";
         }
         return _loc2_;
      }
   }
}

