package script.net_bingo
{
   import InputPad.InputPadKeyCode;
   import KeyHelp.KeyHelpCode;
   import flash.display.MovieClip;
   import flash.external.ExternalInterface;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol15")]
   public class nut_reward extends MovieClip
   {
      
      public var all_help:nut_help;
      
      public var all_help2:nut_help2;
      
      public var all_list_win:nut_list_win;
      
      public var GetCumuAchievementParam:Function;
      
      public var GetNowAchievementNum:Function;
      
      private var m_info:nut_info = null;
      
      private var m_win:nut_list_win = null;
      
      private var m_help:nut_help = null;
      
      private var m_func:Function = null;
      
      private var m_pad:InputPadKeyCode = new InputPadKeyCode();
      
      private var m_keyHelp:KeyHelpCode;
      
      public function nut_reward()
      {
         super();
         addFrameScript(4,this.frame5,8,this.frame9);
         this.m_info = this["all_info"];
         this.m_win = this["all_list_win"];
         this.m_help = this["all_help"];
         stop();
         this.visible = false;
      }
      
      public function OnUpdate() : *
      {
         if(this.m_func != null)
         {
            this.m_func();
         }
      }
      
      public function RequestOpen() : *
      {
         this.visible = true;
         gotoAndPlay("in");
         this.m_func = this.StateOpen;
         var _loc1_:Array = new Array();
         var _loc2_:CumulativeAchievementParam = new CumulativeAchievementParam();
         var _loc3_:uint = uint(this.GetCumuAchievementParam(_loc1_));
         var _loc4_:uint = uint(this.GetNowAchievementNum());
         this.m_win.SetRewardParamArray(_loc1_,_loc4_);
         trace("# paramArr        : " + _loc1_);
         trace("# paramNum        : " + _loc3_);
         trace("# num             : " + _loc4_);
         trace("# paramArr.length : " + _loc1_.length);
         var _loc5_:uint = 0;
         while(_loc5_ < _loc1_.length)
         {
            if(_loc4_ < _loc1_[_loc5_].m_cumuAchievementNum)
            {
               break;
            }
            _loc5_++;
         }
         if(_loc5_ >= _loc1_.length)
         {
            this.m_help.SetCompRewardInfo();
         }
         else
         {
            this.m_help.SetNextRewardInfo(_loc4_,_loc1_[_loc5_].m_cumuAchievementNum,_loc1_[_loc5_].m_itemId);
         }
      }
      
      public function IsClosed() : Boolean
      {
         var _loc1_:Boolean = false;
         if(currentLabel == "end")
         {
            _loc1_ = true;
         }
         return _loc1_;
      }
      
      private function StateOpen() : *
      {
         trace(" m_cumuReward.currentFrame :" + this.currentFrame);
         trace(" m_cumuReward.currentFrame :" + this.currentLabel);
         if(currentLabel == "loop")
         {
            this.m_func = this.StateMain;
         }
      }
      
      private function StateMain() : *
      {
         if(this.m_pad.GetPadPress() & this.m_pad.GetKeyInputBtn_Cancel())
         {
            ExternalInterface.call("RequestPlaySE_Cancel");
            gotoAndPlay("out");
            this.m_func = this.StateClose;
            this.m_keyHelp.PopKeyHelp();
         }
         else
         {
            this.m_win.OnUpdate();
         }
      }
      
      private function StateClose() : *
      {
      }
      
      internal function frame5() : *
      {
         stop();
      }
      
      internal function frame9() : *
      {
         stop();
      }
   }
}

