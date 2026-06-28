package script.duel_boss
{
   import flash.display.MovieClip;
   import flash.events.Event;
   import script.d_boss_plat.nut_btn;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol90")]
   public class nut_vision extends MovieClip
   {
      
      public var mc_btn:nut_btn;
      
      public var mc_eff_re:MovieClip;
      
      private var m_effArr:Array = null;
      
      private var m_btn:MovieClip = null;
      
      private var m_approachMessage:MovieClip = null;
      
      private var m_btnEffect:MovieClip = null;
      
      private var m_isEnableEffect:Boolean = false;
      
      public function nut_vision()
      {
         super();
         addFrameScript(10,this.frame11,27,this.frame28,45,this.frame46);
         stop();
         this.m_effArr = new Array();
         this.m_btn = this["mc_btn"];
         this.m_approachMessage = this["mc_app"];
         this.m_btnEffect = this["mc_eff_re"];
         this.m_btnEffect.visible = false;
         if(this.m_approachMessage)
         {
            this.m_approachMessage.visible = false;
         }
         addEventListener(Event.REMOVED_FROM_STAGE,this.OnRemove);
      }
      
      public function OnRemove(param1:Event) : *
      {
         if(hasEventListener(Event.ENTER_FRAME) == true)
         {
            removeEventListener(Event.ENTER_FRAME,this.OnUpdate);
         }
         if(hasEventListener(Event.REMOVED_FROM_STAGE) == true)
         {
            removeEventListener(Event.REMOVED_FROM_STAGE,this.OnRemove);
         }
      }
      
      public function OnUpdate(param1:Event) : *
      {
         var _loc2_:* = 0;
         var _loc3_:Boolean = false;
         if(this.m_effArr.length > 0)
         {
            _loc2_ = int(this.m_effArr.length - 1);
            while(_loc2_ >= 0)
            {
               if(this.m_effArr[_loc2_].currentFrame >= this.m_effArr[_loc2_].totalFrames - 1)
               {
                  this.m_effArr[_loc2_].stop();
               }
               _loc2_--;
            }
            _loc3_ = true;
            while(_loc3_)
            {
               if(this.m_effArr[this.m_effArr.length - 1].currentFrame >= this.m_effArr[this.m_effArr.length - 1].totalFrames - 1)
               {
                  removeChild(this.m_effArr[this.m_effArr.length - 1]);
                  this.m_effArr.pop();
                  if(this.m_effArr.length <= 0)
                  {
                     _loc3_ = false;
                  }
               }
               else
               {
                  _loc3_ = false;
               }
            }
         }
      }
      
      public function ChangeButtonIcon(param1:String) : *
      {
         this.m_btn.gotoAndStop(param1);
         if(param1 == "stk_tilt_lr" || param1 == "stk_l_r" || param1 == "stk_l_l" || param1 == "stk_l_up" || param1 == "stk_l_dwn")
         {
            this.m_btn.play();
         }
      }
      
      public function RequestInputEffect() : *
      {
         var _loc1_:MovieClip = null;
         if(currentLabel == "loop")
         {
            _loc1_ = new MovieClip();
            addChildAt(_loc1_,getChildIndex(this.m_btn));
            _loc1_.play();
            this.m_effArr.unshift(_loc1_);
            if(hasEventListener(Event.ENTER_FRAME) == false)
            {
               addEventListener(Event.ENTER_FRAME,this.OnUpdate);
            }
         }
      }
      
      public function SetPos(param1:Number, param2:Number) : *
      {
         x = param1;
         y = param2;
      }
      
      public function SetScale(param1:Number) : *
      {
         scaleX = param1;
         scaleY = param1;
      }
      
      public function SetButtonId(param1:String) : *
      {
         if(param1.indexOf("_loop") != -1)
         {
            this.m_btn.gotoAndPlay(param1);
         }
         else
         {
            this.m_btn.gotoAndStop(param1);
         }
      }
      
      public function IsEndAnm() : Boolean
      {
         var _loc1_:Boolean = false;
         if(currentLabel == "ng_end" || currentLabel == "ok_end")
         {
            _loc1_ = true;
         }
         return _loc1_;
      }
      
      public function IsLoopAnm() : Boolean
      {
         var _loc1_:Boolean = false;
         if(currentLabel == "loop")
         {
            _loc1_ = true;
         }
         return _loc1_;
      }
      
      public function IsVisible() : Boolean
      {
         return visible;
      }
      
      public function SetVisible(param1:Boolean) : *
      {
         visible = param1;
      }
      
      public function SetApproachMessage(param1:Boolean) : *
      {
         this.m_approachMessage.visible = true;
         if(param1 == true)
         {
            this.m_approachMessage.gotoAndPlay("in");
         }
         else
         {
            this.m_approachMessage.gotoAndPlay("out");
         }
      }
      
      public function SetEnableButtomEffect() : *
      {
         this.m_isEnableEffect = true;
      }
      
      public function DisableButtomEffect() : *
      {
         this.m_btnEffect.visible = false;
      }
      
      private function CheckButtomEffect() : *
      {
         this.m_btnEffect.visible = this.m_isEnableEffect;
      }
      
      internal function frame11() : *
      {
         this.stop();
         this.CheckButtomEffect();
      }
      
      internal function frame28() : *
      {
         this.stop();
      }
      
      internal function frame46() : *
      {
         this.stop();
      }
   }
}

