package script.gauge_awk
{
   import flash.display.MovieClip;
   import flash.events.Event;
   
   public class nut_awk_lock extends MovieClip
   {
      
      public static const LOCK_LIMIT_START_FRAME:* = 50;
      
      public static const LOCK_LIMIT_FRAMES:* = 49;
      
      private var m_isDisp:Boolean;
      
      private var m_lockLimitRate:Number;
      
      public function nut_awk_lock()
      {
         super();
         this.visible = false;
      }
      
      public function Initialize() : *
      {
         this.gotoAndStop("end");
         this.visible = true;
         this.m_isDisp = false;
         this.m_lockLimitRate = 0;
         addEventListener(Event.ENTER_FRAME,this.Update);
      }
      
      public function Finalize() : *
      {
         removeEventListener(Event.ENTER_FRAME,this.Update);
      }
      
      public function Update(param1:Event) : *
      {
         var _loc2_:int = 0;
         if(this.m_isDisp == false)
         {
            return;
         }
         if(this.m_lockLimitRate > 0)
         {
            _loc2_ = LOCK_LIMIT_START_FRAME + this.m_lockLimitRate * LOCK_LIMIT_FRAMES;
            this.gotoAndStop(_loc2_);
         }
      }
      
      public function SetDispLockGauge(param1:Boolean) : *
      {
         this.m_isDisp = param1;
         if(this.m_isDisp)
         {
            this.gotoAndPlay("in");
         }
         else
         {
            this.m_lockLimitRate = 0;
            this.gotoAndPlay("out");
         }
      }
      
      public function SetLockLimitRate(param1:Number) : *
      {
         this.m_lockLimitRate = 1 - param1;
      }
   }
}

