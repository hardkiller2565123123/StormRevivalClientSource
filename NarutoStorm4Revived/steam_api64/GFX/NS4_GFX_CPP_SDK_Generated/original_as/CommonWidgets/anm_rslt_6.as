package hist_cmn_brt_fla
{
   import flash.display.MovieClip;
   import script.icon_rate_s.nut_rate_s;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol50")]
   public dynamic class anm_rslt_6 extends MovieClip
   {
      
      public var mc_rslt:nut_rate_s;
      
      public var txt_rslt:smb_font;
      
      public function anm_rslt_6()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_rslt.SetTextSize(25);
         this.txt_rslt.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_rslt.SetTextColor(16775638);
         this.txt_rslt.SetTextFieldWidth(130);
         this.txt_rslt.SetTextFit(true);
      }
   }
}

