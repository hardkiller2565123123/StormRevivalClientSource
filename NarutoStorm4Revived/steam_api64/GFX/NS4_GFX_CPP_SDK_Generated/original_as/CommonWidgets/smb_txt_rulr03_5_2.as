package freebtl_rlt_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol9")]
   public dynamic class smb_txt_rulr03_5 extends MovieClip
   {
      
      public var txt_rulr03:smb_font;
      
      public function smb_txt_rulr03_5()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_rulr03.SetTextColor(smb_font.CCD_COLOR_BLACK);
         this.txt_rulr03.SetTextSize(33);
         if(this.txt_rulr03.IsArabic() == true)
         {
            this.txt_rulr03.SetTextFieldWidth(930);
            this.txt_rulr03.SetOffsetPos(930,0);
            this.txt_rulr03.SetTextPivot(smb_font.CCD_PIVOT_RC);
            this.txt_rulr03.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
         }
         else
         {
            this.txt_rulr03.SetTextFieldWidth(1040);
            this.txt_rulr03.SetTextPivot(smb_font.CCD_PIVOT_LC);
         }
         this.txt_rulr03.SetTextFit(true);
      }
   }
}

