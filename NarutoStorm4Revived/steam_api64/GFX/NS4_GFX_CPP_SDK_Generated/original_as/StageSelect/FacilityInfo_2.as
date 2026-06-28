package script.map_sm
{
   public class FacilityInfo
   {
      
      public var m_iconType:int = 0;
      
      public var m_posX:Number = 0;
      
      public var m_posY:Number = 0;
      
      public var m_stageId:String = "";
      
      public function FacilityInfo(param1:int, param2:Number, param3:Number, param4:String)
      {
         super();
         this.m_iconType = param1;
         this.m_posX = param2;
         this.m_posY = param3;
         this.m_stageId = param4;
      }
   }
}

