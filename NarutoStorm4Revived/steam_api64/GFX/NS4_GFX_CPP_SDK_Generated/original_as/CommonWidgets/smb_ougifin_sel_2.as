package script.custom
{
   import flash.display.MovieClip;
   import script.icon_confirm.nut_conf_s;
   import script.icon_new.nut_new;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol16")]
   public class smb_ougifin_sel extends MovieClip
   {
      
      public var mc_conf_s_icon:nut_conf_s;
      
      public var mc_new_icon:nut_new;
      
      public var txt_ougifin_num:smb_font;
      
      private var m_newIconMC:MovieClip;
      
      private var m_confIconMC:MovieClip;
      
      private var m_indexTextMC:smb_font;
      
      public function smb_ougifin_sel()
      {
         super();
         addFrameScript(0,this.frame1,1,this.frame2,2,this.frame3);
         this.m_newIconMC = this["mc_new_icon"];
         this.m_confIconMC = this["mc_conf_s_icon"];
         this.m_indexTextMC = this["txt_ougifin_num"];
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
      
      public function SetIndexNumber(param1:int) : *
      {
         this.m_indexTextMC.SetText(param1.toString());
      }
      
      internal function frame1() : *
      {
         stop();
         this.txt_ougifin_num.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_ougifin_num.SetTextColor(469645);
         this.txt_ougifin_num.SetDropShadowFilter(11645361);
         this.txt_ougifin_num.SetTextSize(33);
      }
      
      internal function frame2() : *
      {
         stop();
         this.txt_ougifin_num.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_ougifin_num.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_ougifin_num.SetTextSize(33);
      }
      
      internal function frame3() : *
      {
         stop();
         this.txt_ougifin_num.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_ougifin_num.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_ougifin_num.SetTextSize(33);
      }
   }
}

