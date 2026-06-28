package script.gauge_cmn
{
   import flash.display.MovieClip;
   import flash.events.Event;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol94")]
   public class nut_guard extends MovieClip
   {
      
      public var m_nowGuardRate:Number;
      
      public var mc_guard_red2:MovieClip;
      
      public var mc_guard_yellow:MovieClip;
      
      public var mc_guard_blue:MovieClip;
      
      public function nut_guard()
      {
         super();
      }
      
      public function Initialize() : *
      {
         this.m_nowGuardRate = 1;
         addEventListener(Event.ENTER_FRAME,this.Update);
      }
      
      public function Finalize() : *
      {
         removeEventListener(Event.ENTER_FRAME,this.Update);
      }
      
      public function Update(e:Event) : *
      {
         var total:int = this.totalFrames;
         var rate:Number = this.m_nowGuardRate;
         var raw:Number = rate * total;
         var frame:int = rate > 0 ? int(Math.min(total,Math.max(1,Math.ceil(raw)))) : 1;
         this.gotoAndStop(frame);
         var EPS:Number = 0;
         var on:Boolean = rate > EPS;
         this.mc_guard_red2.visible = on;
         this.mc_guard_yellow.visible = on;
         this.mc_guard_blue.visible = on;
      }
      
      public function SetGuardLifeRate(param1:Number) : *
      {
         this.m_nowGuardRate = param1;
      }
   }
}

