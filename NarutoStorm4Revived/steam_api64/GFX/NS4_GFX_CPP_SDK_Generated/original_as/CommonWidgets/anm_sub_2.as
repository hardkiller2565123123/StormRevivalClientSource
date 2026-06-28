package script.start_event_s_brt
{
   import flash.display.Bitmap;
   import flash.display.BitmapData;
   import flash.display.MovieClip;
   import flash.utils.getDefinitionByName;
   import script.icon_navi.nut_navi;
   import script.icon_new.nut_new;
   import script.icon_result2_brt.smb_rslt_ok;
   import script.xcmn_tex00.nut_tex00;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol32")]
   public class anm_sub extends MovieClip
   {
      
      public var dmy_char:nut_tex00;
      
      public var mc_navi:nut_navi;
      
      public var mc_new:nut_new;
      
      public var mc_now:MovieClip;
      
      public var mc_ok:smb_rslt_ok;
      
      private var m_info:EventParam = null;
      
      private var m_okIcon:MovieClip = null;
      
      private var m_naviIcon:MovieClip = null;
      
      private var m_newIcon:MovieClip = null;
      
      private var m_stateIcon:MovieClip = null;
      
      private var m_iconDmy:MovieClip = null;
      
      private var m_charIcon:MovieClip = null;
      
      private var m_isLockIcon:Boolean = true;
      
      public function anm_sub()
      {
         super();
         addFrameScript(29,this.frame30,70,this.frame71,71,this.frame72);
         this.m_okIcon = this["mc_ok"];
         this.m_naviIcon = this["mc_navi"];
         this.m_newIcon = this["mc_new"];
         this.m_stateIcon = this["mc_now"];
         this.m_iconDmy = this["dmy_char"];
         this.m_naviIcon.gotoAndStop("sab");
      }
      
      public function InitEventState(param1:EventParam) : *
      {
         trace(param1);
         this.m_info = param1;
         this.m_okIcon.visible = false;
         this.m_stateIcon.visible = true;
         this.m_isLockIcon = this.m_info.isUnlock;
         trace(this.m_info.stats);
         switch(this.m_info.stats)
         {
            case EventParam.CCD_SUB_EVENT_STATE_ACCEPT:
               this.m_stateIcon.gotoAndStop("now");
               break;
            case EventParam.CCD_SUB_EVENT_STATE_REWARD:
               this.m_stateIcon.gotoAndStop("clear");
               break;
            case EventParam.CCD_SUB_EVENT_STATE_NONE:
               this.m_isLockIcon = true;
               this.m_stateIcon.visible = false;
               break;
            case EventParam.CCD_SUB_EVENT_STATE_VISIBLED_CLEAR:
            case EventParam.CCD_SUB_EVENT_STATE_CLEAR:
               trace("ClearIcon:TRUE");
               this.m_okIcon.visible = true;
            default:
               this.m_stateIcon.visible = false;
         }
         trace("ClearIconState:" + this.m_okIcon.visible);
         this.m_newIcon.visible = this.m_info.isNew;
         this.m_naviIcon.visible = this.m_info.isNavi;
         if(this.m_charIcon != null)
         {
            if(this.m_iconDmy.contains(this.m_charIcon) == true)
            {
               removeChild(this.m_charIcon);
            }
         }
         this.m_charIcon = new MovieClip();
         this.m_charIcon.x = this.m_charIcon.y = 0;
         this.m_iconDmy.addChild(this.m_charIcon);
         trace("CreateCharIcon:" + this.m_info.charIcon);
         var _loc2_:Class = getDefinitionByName(this.m_info.charIcon) as Class;
         var _loc3_:BitmapData = new _loc2_(0,0);
         var _loc4_:Bitmap = new Bitmap(_loc3_);
         _loc4_.smoothing = true;
         _loc4_.x = 0;
         _loc4_.y = 0;
         this.m_charIcon.addChildAt(_loc4_,0);
         this.m_charIcon.x -= this.m_charIcon.width * 0.5;
         this.m_charIcon.y -= this.m_charIcon.height * 0.5;
         if(this.m_isLockIcon == true)
         {
            gotoAndStop("lock");
         }
         else
         {
            gotoAndStop("off");
         }
      }
      
      public function RequestUnlockAnimation() : *
      {
         if(this.m_info.isUnlock == true)
         {
            this.m_info.isUnlock = false;
            this.m_isLockIcon = false;
            gotoAndPlay("unlock");
         }
      }
      
      public function RequestTargetOnAnimation() : *
      {
         if(this.m_isLockIcon == false)
         {
            gotoAndPlay("on");
         }
      }
      
      public function RequestTargetOffAnimation() : *
      {
         if(this.m_isLockIcon == false)
         {
            gotoAndPlay("off");
         }
      }
      
      public function GetEventParam() : EventParam
      {
         return this.m_info;
      }
      
      public function GetNaviEnable() : Boolean
      {
         return this.m_info.isNavi;
      }
      
      public function SetNaviChange() : *
      {
         this.m_info.isNavi = !this.m_info.isNavi;
         this.m_naviIcon.visible = this.m_info.isNavi;
      }
      
      public function SetDisableNewIcon() : *
      {
         this.m_info.isNew = false;
         this.m_newIcon.visible = false;
      }
      
      public function IsLockIcon() : Boolean
      {
         trace("ISLockIcon:" + this.m_isLockIcon);
         return this.m_isLockIcon;
      }
      
      internal function frame30() : *
      {
         gotoAndPlay("on");
      }
      
      internal function frame71() : *
      {
         this.stop();
      }
      
      internal function frame72() : *
      {
         this.stop();
      }
   }
}

