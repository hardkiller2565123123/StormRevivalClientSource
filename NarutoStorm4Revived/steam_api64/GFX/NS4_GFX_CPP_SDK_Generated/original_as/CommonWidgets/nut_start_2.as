package script.gametitle_lang
{
   import flash.display.MovieClip;
   import flash.events.Event;
   
   public class nut_start extends MovieClip
   {
      
      private const CCD_DEFAULT_WIDTH:Number = 552;
      
      private const CCD_DEFAULT_HEIGHT:Number = 94;
      
      private const CCD_ANM_MAX_FRAME:int = 14;
      
      private const CCD_ANM_WIDTH_RATE:Number = 0.786;
      
      private const CCD_ANM_HEIGHT_RATE:Number = 0.136;
      
      private var m_anmVec:int = 0;
      
      private var m_anmFrame:int = 0;
      
      public function nut_start()
      {
         super();
         var _loc1_:MovieClip = this["mc_btn"];
         _loc1_.gotoAndStop("btn_1");
         this.m_anmVec = 1;
         addEventListener(Event.REMOVED_FROM_STAGE,this.OnRemove);
      }
      
      private function OnRemove(param1:Event) : *
      {
         if(hasEventListener(Event.ENTER_FRAME) != 0)
         {
            removeEventListener(Event.ENTER_FRAME,this.OnUpdate);
         }
         removeEventListener(Event.REMOVED_FROM_STAGE,this.OnRemove);
      }
      
      public function StartAnm() : *
      {
         if(hasEventListener(Event.ENTER_FRAME) == 0)
         {
            addEventListener(Event.ENTER_FRAME,this.OnUpdate);
         }
      }
      
      private function OnUpdate(param1:Event) : *
      {
         if(this.m_anmFrame++ < this.CCD_ANM_MAX_FRAME)
         {
            width += this.m_anmVec * this.CCD_ANM_WIDTH_RATE;
            height += this.m_anmVec * this.CCD_ANM_HEIGHT_RATE;
         }
         else
         {
            if(this.m_anmVec < 0)
            {
               width = this.CCD_DEFAULT_WIDTH;
               height = this.CCD_DEFAULT_HEIGHT;
            }
            this.m_anmFrame = 0;
            this.m_anmVec = -this.m_anmVec;
         }
      }
      
      public function ChangeBtn() : void
      {
         var _loc1_:MovieClip = this["mc_btn"];
         if(_loc1_.currentFrameLabel == "btn_1")
         {
            _loc1_.gotoAndStop("btn_2");
         }
         else
         {
            _loc1_.gotoAndStop("btn_1");
         }
      }
   }
}

