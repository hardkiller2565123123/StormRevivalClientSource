package script.duel_boss_help
{
   import Struct.MessageParam;
   import flash.external.ExternalInterface;
   
   public class nut_help_phase01
   {
      
      public static const CCD_KEY_ATK:int = 0;
      
      public static const CCD_KEY_GRD:int = 1;
      
      public static const CCD_KEY_KRJ:int = 2;
      
      public static const CCD_KEY_SKL:int = 3;
      
      public static const CCD_KEY_CHD:int = 4;
      
      public static const CCD_KEY_JMP:int = 5;
      
      public static const CCD_KEY_CHC:int = 6;
      
      public static const CCD_KEY_SRK:int = 7;
      
      public static const CCD_HELP_NUM:int = 8;
      
      private const CCD_HELP_MSG_1:String = "commandlist_demo_00";
      
      private const CCD_HELP_MSG_2:String = "commandlist_demo_08";
      
      private const CCD_HELP_MSG_3:String = "commandlist_demo_10";
      
      private const CCD_HELP_MSG_4:String = "commandlist_demo_12";
      
      private const CCD_HELP_MSG_5:String = "commandlist_demo_14";
      
      private const CCD_HELP_MSG_6:String = "commandlist_demo_04";
      
      private const CCD_HELP_MSG_7:String = "commandlist_demo_17";
      
      private const CCD_HELP_MSG_8:String = "commandlist_demo_02";
      
      private const CCD_ATK_CMD:String = "commandlist_demo_01";
      
      private const CCD_SRK_CMD:String = "commandlist_demo_03";
      
      private const CCD_JMP_CMD:String = "commandlist_demo_05";
      
      private const CCD_CHC_CMD:String = "commandlist_012";
      
      private const CCD_GRD_CMD:String = "commandlist_demo_09";
      
      private const CCD_KRJ_CMD:String = "commandlist_demo_11";
      
      private const CCD_SKL_CMD:String = "commandlist_demo_13";
      
      private const CCD_CHD_CMD:String = "commandlist_demo_15";
      
      private var m_paramArr:Array = new Array();
      
      public function nut_help_phase01()
      {
         super();
         var _loc1_:int = 0;
         while(_loc1_ < CCD_HELP_NUM)
         {
            this.m_paramArr.push(new MessageParam());
            _loc1_++;
         }
         this.m_paramArr[CCD_KEY_ATK].m_msg = String(ExternalInterface.call("MessageConvert",this.CCD_HELP_MSG_1));
         this.m_paramArr[CCD_KEY_GRD].m_msg = String(ExternalInterface.call("MessageConvert",this.CCD_HELP_MSG_2));
         this.m_paramArr[CCD_KEY_KRJ].m_msg = String(ExternalInterface.call("MessageConvert",this.CCD_HELP_MSG_3));
         this.m_paramArr[CCD_KEY_SKL].m_msg = String(ExternalInterface.call("MessageConvert",this.CCD_HELP_MSG_4));
         this.m_paramArr[CCD_KEY_CHD].m_msg = String(ExternalInterface.call("MessageConvert",this.CCD_HELP_MSG_5));
         this.m_paramArr[CCD_KEY_JMP].m_msg = String(ExternalInterface.call("MessageConvert",this.CCD_HELP_MSG_6));
         this.m_paramArr[CCD_KEY_CHC].m_msg = String(ExternalInterface.call("MessageConvert",this.CCD_HELP_MSG_7));
         this.m_paramArr[CCD_KEY_SRK].m_msg = String(ExternalInterface.call("MessageConvert",this.CCD_HELP_MSG_8));
         this.m_paramArr[CCD_KEY_ATK].m_cmd = String(ExternalInterface.call("MessageConvert",this.CCD_ATK_CMD));
         this.m_paramArr[CCD_KEY_SRK].m_cmd = String(ExternalInterface.call("MessageConvert",this.CCD_SRK_CMD));
         this.m_paramArr[CCD_KEY_JMP].m_cmd = String(ExternalInterface.call("MessageConvert",this.CCD_JMP_CMD));
         this.m_paramArr[CCD_KEY_CHC].m_cmd = String(ExternalInterface.call("MessageConvert",this.CCD_CHC_CMD));
         this.m_paramArr[CCD_KEY_GRD].m_cmd = String(ExternalInterface.call("MessageConvert",this.CCD_GRD_CMD));
         this.m_paramArr[CCD_KEY_KRJ].m_cmd = String(ExternalInterface.call("MessageConvert",this.CCD_KRJ_CMD));
         this.m_paramArr[CCD_KEY_SKL].m_cmd = String(ExternalInterface.call("MessageConvert",this.CCD_SKL_CMD));
         this.m_paramArr[CCD_KEY_CHD].m_cmd = String(ExternalInterface.call("MessageConvert",this.CCD_CHD_CMD));
      }
      
      public function GetMessage(param1:int) : String
      {
         var _loc2_:String = "UndefinedMessage";
         if(this.m_paramArr[param1] != null)
         {
            _loc2_ = this.m_paramArr[param1].m_msg;
         }
         return _loc2_;
      }
      
      public function GetCommand(param1:int) : String
      {
         var _loc2_:String = "UndefinedMessage";
         if(this.m_paramArr[param1] != null)
         {
            _loc2_ = this.m_paramArr[param1].m_cmd;
         }
         return _loc2_;
      }
   }
}

