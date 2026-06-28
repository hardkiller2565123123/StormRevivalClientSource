package script.duel_boss
{
   public class IaGaugeParam
   {
      
      public var m_intervalFrame:int;
      
      public var m_nowTime:uint;
      
      public var m_nowGauge:uint;
      
      public var m_posX:Number;
      
      public var m_posY:Number;
      
      public var m_scaleX:Number;
      
      public var m_scaleY:Number;
      
      public var m_isInput:Boolean;
      
      public function IaGaugeParam(param1:int = 0, param2:uint = 0, param3:uint = 0, param4:Number = 0, param5:Number = 0, param6:Number = 0, param7:Number = 0, param8:Boolean = false)
      {
         super();
         this.m_intervalFrame = param1;
         this.m_nowTime = param2;
         this.m_nowGauge = param3;
         this.m_posX = param4;
         this.m_posY = param5;
         this.m_scaleX = param6;
         this.m_scaleY = param7;
         this.m_isInput = param8;
      }
   }
}

