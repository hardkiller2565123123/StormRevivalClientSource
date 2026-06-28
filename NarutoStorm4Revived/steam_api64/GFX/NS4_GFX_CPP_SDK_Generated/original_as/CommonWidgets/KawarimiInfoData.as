package script.infoData
{
   public class KawarimiInfoData extends InfoDataBase
   {
      
      public var m_labelName:String;
      
      public var m_itemName:String;
      
      public function KawarimiInfoData(param1:Array)
      {
         super(param1);
         var _loc2_:int = CCD_INIT_PARAM_NUM;
         this.m_labelName = param1[_loc2_];
         this.m_itemName = param1[++_loc2_];
      }
   }
}

