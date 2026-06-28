package result_net_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol14")]
   public dynamic class smb_rd_plate_5 extends MovieClip
   {
      
      public var mc_arrow:MovieClip;
      
      public var txt_rd_next:smb_font;
      
      public var txt_rd_current:smb_font;
      
      public function smb_rd_plate_5()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_rd_next.SetText("上忍_ABCgy■■■■■■■■■■■■■■■■■■■");
         this.txt_rd_current.SetText("中忍_ABCgy■■■■■■■■■■■■■■■■■■■");
         this.txt_rd_next.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_rd_next.SetTextColor(798121);
         this.txt_rd_next.SetDropShadowFilter(11645361);
         this.txt_rd_next.SetTextFieldWidth(536);
         this.txt_rd_next.SetTextFit(true);
         this.txt_rd_current.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_rd_current.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_rd_current.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_rd_current.SetTextFieldWidth(536);
         this.txt_rd_current.SetTextFit(true);
      }
   }
}

