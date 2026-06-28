package duel_cond_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol31")]
   public dynamic class anm_bns_title_14 extends MovieClip
   {
      
      public var txt_cond_tit:smb_font;
      
      public function anm_bns_title_14()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_cond_tit.SetText("ボーナス条件　ABC_gy");
         this.txt_cond_tit.SetTextSize(28);
         this.txt_cond_tit.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_cond_tit.SetTextColor(16759422);
         this.txt_cond_tit.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
      }
   }
}

