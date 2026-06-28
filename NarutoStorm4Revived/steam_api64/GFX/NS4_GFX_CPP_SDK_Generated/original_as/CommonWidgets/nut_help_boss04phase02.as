package script.duel_boss_help
{
   import Struct.MessageParam;
   import flash.external.ExternalInterface;
   
   public class nut_help_boss04phase02
   {
      
      public static const CCD_KEY_ATK:int = 0;
      
      public static const CCD_KEY_SRK:int = 1;
      
      public static const CCD_HELP_NUM:int = 2;
      
      private const CCD_HELP_MSG_1:String = "commandlist_demo_29";
      
      private const CCD_HELP_MSG_2:String = "commandlist_demo_31";
      
      private const CCD_LMO_CMD:String = "commandlist_demo_30";
      
      private const CCD_RMO_CMD:String = "commandlist_demo_32";
      
      private var m_paramArr:Array = new Array();
      
      public function nut_help_boss04phase02()
      {
         super();
         this.m_paramArr.push(new MessageParam());
         this.m_paramArr.push(new MessageParam());
         this.m_paramArr[0].m_msg = String(ExternalInterface.call("MessageConvert",this.CCD_HELP_MSG_1));
         this.m_paramArr[1].m_msg = String(ExternalInterface.call("MessageConvert",this.CCD_HELP_MSG_2));
         this.m_paramArr[0].m_cmd = String(ExternalInterface.call("MessageConvert",this.CCD_LMO_CMD));
         this.m_paramArr[1].m_cmd = String(ExternalInterface.call("MessageConvert",this.CCD_RMO_CMD));
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

