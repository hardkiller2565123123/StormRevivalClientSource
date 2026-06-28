package script.gauge_p
{
   import flash.display.MovieClip;
   import flash.events.Event;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol10")]
   public class all_team extends MovieClip
   {
      
      public static const NORMAL_MAX_FRAME:* = 100;
      
      public static const AWAKE_LIMIT_START_FRAME:* = 120;
      
      public static const AWAKE_LIMIT_FRAMES:* = 100;
      
      private var m_teamGaugeRate:Number;
      
      private var m_awakeLimitRate:Number;
      
      private var m_isMax:Boolean;
      
      private var m_isAwake:Boolean;
      
      public function all_team()
      {
         super();
         addFrameScript(0,this.frame1,118,this.frame119,220,this.frame221);
      }
      
      public function Initialize() : *
      {
         this.m_teamGaugeRate = 0;
         this.m_awakeLimitRate = 0;
         this.m_isMax = false;
         this.m_isAwake = false;
         addEventListener(Event.ENTER_FRAME,this.Update);
      }
      
      public function Finalize() : *
      {
         removeEventListener(Event.ENTER_FRAME,this.Update);
      }
      
      public function Update(param1:Event) : *
      {
         var _loc2_:int = 0;
         var _loc3_:int = 0;
         if(this.m_isAwake)
         {
            _loc2_ = AWAKE_LIMIT_START_FRAME + this.m_awakeLimitRate * AWAKE_LIMIT_FRAMES;
            this.gotoAndStop(_loc2_);
         }
         else if(this.m_isMax == false)
         {
            _loc3_ = this.m_teamGaugeRate * NORMAL_MAX_FRAME;
            this.gotoAndStop(_loc3_);
         }
         else if(this.currentLabel != "max")
         {
            this.gotoAndPlay("max");
         }
      }
      
      public function SetVisible(param1:Boolean) : *
      {
         this.visible = param1;
      }
      
      public function SetTeamGaugeRate(param1:Number) : *
      {
         this.m_teamGaugeRate = param1;
         if(this.m_teamGaugeRate >= 1)
         {
            if(this.m_isMax == false)
            {
               this.m_isMax = true;
               this.gotoAndPlay("max");
            }
         }
         else
         {
            this.m_isMax = false;
         }
      }
      
      public function SetAwake(param1:Boolean) : *
      {
         this.m_isAwake = param1;
      }
      
      public function SetAwakeLimitRate(param1:Number) : *
      {
         this.m_awakeLimitRate = 1 - param1;
      }
      
      internal function frame1() : *
      {
         this.stop();
      }
      
      internal function frame119() : *
      {
         gotoAndPlay("max");
      }
      
      internal function frame221() : *
      {
         this.stop();
      }
   }
}

