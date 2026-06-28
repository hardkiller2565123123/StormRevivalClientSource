package script.infoData
{
   public class OugiFinInfoData extends InfoDataBase
   {
      
      public var m_msgId:String;
      
      public var m_imgFileName:String;
      
      public function OugiFinInfoData(param1:Array)
      {
         super(param1);
         var _loc2_:int = CCD_INIT_PARAM_NUM;
         this.m_msgId = param1[_loc2_];
         this.m_imgFileName = param1[++_loc2_];
      }
   }
}

