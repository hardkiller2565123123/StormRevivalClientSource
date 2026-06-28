package hist_cmn_fla
{
   import flash.display.MovieClip;
   import script.icon_rate_s.nut_rate_s;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol44")]
   public dynamic class anm_rslt_63 extends MovieClip
   {
      
      public var mc_rslt:nut_rate_s;
      
      public var txt_rslt:smb_font;
      
      public function anm_rslt_63()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_rslt.SetText("総合評価_ABCgy");
         this.txt_rslt.SetTextSize(25);
         this.txt_rslt.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_rslt.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_rslt.SetTextFieldWidth(130);
         this.txt_rslt.SetTextFit(true);
      }
   }
}

