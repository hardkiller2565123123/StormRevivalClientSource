package result_main_fla
{
   import flash.display.MovieClip;
   import script.icon_btl.nut_icon_btl;
   import script.icon_rate_s.nut_rate_s;
   import script.icon_up.nut_up1;
   import script.result_main.anm_textbar00;
   import script.xcmn_font.smb_font;
   import script.xcmn_tex00.nut_tex00;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol125")]
   public dynamic class anm_boss_c_11 extends MovieClip
   {
      
      public var dmy_char1:nut_tex00;
      
      public var dmy_char2:nut_tex00;
      
      public var mc_btl:nut_icon_btl;
      
      public var mc_rate:nut_rate_s;
      
      public var mc_txtbar:anm_textbar00;
      
      public var mc_up:nut_up1;
      
      public var txt_chap:smb_font;
      
      public function anm_boss_c_11()
      {
         super();
         addFrameScript(0,this.frame1,1,this.frame2);
      }
      
      internal function frame1() : *
      {
         this.stop();
         this.txt_chap.SetTextFieldWidth(570);
         this.txt_chap.SetTextFit(true);
         this.txt_chap.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_chap.SetTextSize(28);
         this.txt_chap.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_chap.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
      }
      
      internal function frame2() : *
      {
         this.txt_chap.SetTextColor(4473924);
         this.txt_chap.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
      }
   }
}

