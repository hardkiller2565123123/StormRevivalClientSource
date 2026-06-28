package script.gauge_awk
{
   import flash.display.MovieClip;
   import flash.events.Event;
   
   public class nut_awk extends MovieClip
   {
      
      public static const CCD_AWAKE_GAUGE_NORMAL:* = 0;
      
      public static const CCD_AWAKE_GAUGE_TEAM:* = 1;
      
      public static const ON_HOLD_START_FRAME:* = 40;
      
      public static const ON_HOLD_FRAMES:* = 49;
      
      public static const AWAKE_LIMIT_START_FRAME:* = 105;
      
      public static const AWAKE_LIMIT_FRAMES:* = 49;
      
      private var m_isDisp:Boolean;
      
      private var m_isChakraMax:Boolean;
      
      private var m_isAwake:Boolean;
      
      private var m_awakeGaugeRate:Number;
      
      private var m_awakeLimitRate:Number;
      
      public function nut_awk()
      {
         super();
         this.ChangeGaugeType(CCD_AWAKE_GAUGE_TEAM);
         this.ChangeGaugeType(CCD_AWAKE_GAUGE_NORMAL);
      }
      
      public function Initialize() : *
      {
         this.m_isDisp = false;
         this.m_isChakraMax = false;
         this.m_isAwake = false;
         this.m_awakeGaugeRate = 0;
         this.m_awakeLimitRate = 0;
         addEventListener(Event.ENTER_FRAME,this.Update);
      }
      
      public function Finalize() : *
      {
         removeEventListener(Event.ENTER_FRAME,this.Update);
      }
      
      public function Update(param1:Event) : *
      {
         var _loc3_:int = 0;
         var _loc4_:int = 0;
         if(this.m_isDisp == false)
         {
            return;
         }
         var _loc2_:MovieClip = this.GetCurrentAwakeGauge();
         if(this.m_isAwake)
         {
            if(_loc2_.currentLabel != "awk_start")
            {
               _loc3_ = AWAKE_LIMIT_START_FRAME + this.m_awakeLimitRate * AWAKE_LIMIT_FRAMES;
               _loc2_.gotoAndStop(_loc3_);
            }
         }
         else if(this.m_isChakraMax)
         {
            if(this.m_awakeGaugeRate > 0)
            {
               if(_loc2_.currentLabel != "on_in")
               {
                  _loc4_ = ON_HOLD_START_FRAME + this.m_awakeGaugeRate * ON_HOLD_FRAMES;
                  _loc2_.gotoAndStop(_loc4_);
               }
            }
            else if(_loc2_.currentLabel == "off_in" || _loc2_.currentLabel == "off_loop")
            {
               _loc2_.gotoAndPlay("on_in");
            }
            else if(_loc2_.currentLabel != "on_in" && _loc2_.currentLabel != "on_loop")
            {
               _loc2_.gotoAndPlay("on_loop");
            }
         }
         else if(_loc2_.currentLabel != "on_out" && _loc2_.currentLabel != "off_loop")
         {
            _loc2_.gotoAndPlay("on_out");
         }
      }
      
      public function SetChakraMax(param1:Boolean) : *
      {
         this.m_isChakraMax = param1;
      }
      
      public function SetDispAwakeGauge(param1:Boolean) : *
      {
         var _loc2_:MovieClip = this.GetCurrentAwakeGauge();
         this.m_isDisp = param1;
         if(this.m_isDisp)
         {
            if(_loc2_.currentLabel != "off_in" && _loc2_.currentLabel != "off_loop")
            {
               _loc2_.gotoAndPlay("off_in");
            }
         }
         else if(_loc2_.currentLabel == "awk_loop")
         {
            _loc2_.gotoAndPlay("awk_end");
         }
         else
         {
            _loc2_.gotoAndPlay("off_out");
         }
      }
      
      public function SetAwake(param1:Boolean) : *
      {
         var _loc2_:MovieClip = null;
         this.m_isAwake = param1;
         if(this.m_isAwake)
         {
            _loc2_ = this.GetCurrentAwakeGauge();
            if(_loc2_.currentLabel != "awk_start" && _loc2_.currentLabel != "limit_go")
            {
               _loc2_.gotoAndPlay("awk_start");
            }
         }
      }
      
      public function SetAwakeGaugeRate(param1:Number) : *
      {
         this.m_awakeGaugeRate = param1;
      }
      
      public function SetAwakeLimitRate(param1:Number) : *
      {
         this.m_awakeLimitRate = 1 - param1;
      }
      
      private function GetCurrentAwakeGauge() : MovieClip
      {
         var _loc1_:MovieClip = null;
         if(this.currentLabel == "nomal")
         {
            _loc1_ = MovieClip(this["mc_awk"]);
         }
         else if(this.currentLabel == "team")
         {
            _loc1_ = MovieClip(this["mc_awk_team"]);
         }
         return _loc1_;
      }
      
      public function ChangeGaugeType(param1:int) : *
      {
         var _loc2_:MovieClip = null;
         var _loc3_:MovieClip = null;
         switch(param1)
         {
            case CCD_AWAKE_GAUGE_NORMAL:
               this.gotoAndStop("nomal");
               _loc2_ = MovieClip(this["mc_awk"]);
               if(_loc2_)
               {
                  _loc2_.gotoAndStop(_loc2_.totalFrames - 1);
               }
               break;
            case CCD_AWAKE_GAUGE_TEAM:
               this.gotoAndStop("team");
               _loc3_ = MovieClip(this["mc_awk_team"]);
               if(_loc3_)
               {
                  _loc3_.gotoAndPlay(_loc3_.totalFrames - 1);
               }
         }
      }
   }
}

