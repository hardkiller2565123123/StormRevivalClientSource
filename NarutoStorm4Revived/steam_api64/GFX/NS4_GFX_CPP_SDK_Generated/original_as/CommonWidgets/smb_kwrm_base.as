package script.custom
{
   import flash.display.MovieClip;
   import script.icon_kwrm_s.nut_kwrm_s;
   import script.icon_new.nut_none;
   import script.icon_ng.nut_ng;
   import script.xcmn_menu.nut_frame_1;
   import script.xcmn_menu.nut_frame_2;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol19")]
   public class smb_kwrm_base extends MovieClip
   {
      
      public var mc_kwrm_base:MovieClip;
      
      public var mc_kwrm_edit:nut_frame_2;
      
      public var mc_kwrm_ng:nut_ng;
      
      public var mc_kwrm_off:MovieClip;
      
      public var mc_kwrm_s:nut_kwrm_s;
      
      public var mc_kwrm_sel:nut_frame_1;
      
      public var mc_none:nut_none;
      
      internal var m_iconMC:MovieClip;
      
      internal var m_noneIconMC:MovieClip;
      
      public function smb_kwrm_base()
      {
         super();
         addFrameScript(0,this.frame1);
         stop();
         this.m_iconMC = this["mc_kwrm_s"];
         this.m_noneIconMC = this["mc_none"];
         this.SetVisibleNoneIcon(false);
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
      
      public function SetImpossible() : *
      {
         this.gotoAndStop("impos");
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

