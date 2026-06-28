package script.gauge_cmn
{
   import flash.display.MovieClip;
   import flash.events.Event;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol50")]
   public class nut_kwrm extends MovieClip
   {
      
      public var m_nowDodgeRate:Number;
      
      public function nut_kwrm()
      {
         super();
         addFrameScript(0,this.frame1,29,this.frame30,59,this.frame60,89,this.frame90,119,this.frame120);
      }
      
      public function Initialize() : *
      {
         this.m_nowDodgeRate = 1;
         addEventListener(Event.ENTER_FRAME,this.Update);
      }
      
      public function Finalize() : *
      {
         removeEventListener(Event.ENTER_FRAME,this.Update);
      }
      
      public function Update(param1:Event) : *
      {
         var _loc2_:int = this.totalFrames;
         var _loc3_:int = this.m_nowDodgeRate * _loc2_;
         this.gotoAndStop(_loc3_);
      }
      
      public function SetDodgeRate(param1:Number) : *
      {
         this.m_nowDodgeRate = param1;
      }
      
      internal function frame1() : *
      {
         this.stop();
      }
      
      internal function frame30() : *
      {
         this.stop();
      }
      
      internal function frame60() : *
      {
         this.stop();
      }
      
      internal function frame90() : *
      {
         this.stop();
      }
      
      internal function frame120() : *
      {
         this.stop();
      }
   }
}

