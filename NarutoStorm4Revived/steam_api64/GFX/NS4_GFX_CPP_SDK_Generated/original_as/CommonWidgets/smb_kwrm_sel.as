package script.custom
{
   import flash.display.MovieClip;
   import script.icon_confirm.nut_conf_s;
   import script.icon_kwrm_s.nut_kwrm_s;
   import script.icon_new.nut_new;
   import script.icon_new.nut_none;
   import script.xcmn_menu.nut_frame_1;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol4")]
   public class smb_kwrm_sel extends MovieClip
   {
      
      public var mc_conf_s_icon:nut_conf_s;
      
      public var mc_icon_s:nut_kwrm_s;
      
      public var mc_kwrm_sel:nut_frame_1;
      
      public var mc_new_icon:nut_new;
      
      public var mc_none:nut_none;
      
      private var m_newIconMC:MovieClip;
      
      private var m_confIconMC:MovieClip;
      
      private var m_iconMC:MovieClip;
      
      private var m_noneIconMC:MovieClip;
      
      public function smb_kwrm_sel()
      {
         super();
         addFrameScript(0,this.frame1);
         this.m_newIconMC = this["mc_new_icon"];
         this.m_confIconMC = this["mc_conf_s_icon"];
         this.m_iconMC = this["mc_icon_s"];
         this.m_noneIconMC = this["mc_none"];
      }
      
      public function SetSelect() : *
      {
         this.gotoAndStop("on");
      }
      
      public function SetDisable() : *
      {
         this.gotoAndStop("off");
      }
      
      public function SetEnable() : *
      {
         this.gotoAndStop("normal");
      }
      
      public function SetNewIcon(param1:Boolean) : *
      {
         this.m_newIconMC.visible = param1;
      }
      
      public function SetConfirmIcon(param1:Boolean) : *
      {
         this.m_confIconMC.visible = param1;
      }
      
      public function ChangeIcon(param1:String) : *
      {
         this.m_iconMC.gotoAndStop(param1);
      }
      
      public function SetVisibleNoneIcon(param1:Boolean) : *
      {
         this.m_noneIconMC.visible = param1;
         this.m_iconMC.visible = !param1;
      }
      
      internal function frame1() : *
      {
         stop();
      }
   }
}

