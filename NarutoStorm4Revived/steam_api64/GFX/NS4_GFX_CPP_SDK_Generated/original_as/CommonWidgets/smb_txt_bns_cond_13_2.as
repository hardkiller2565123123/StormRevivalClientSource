package duel_cond_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol29")]
   public dynamic class smb_txt_bns_cond_13 extends MovieClip
   {
      
      public var txt_bns_cond:smb_font;
      
      public function smb_txt_bns_cond_13()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         if(this.txt_bns_cond.IsArabic() == true)
         {
            this.txt_bns_cond.SetTextPivot(smb_font.CCD_PIVOT_RC);
            this.txt_bns_cond.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
         }
         else
         {
            this.txt_bns_cond.SetTextPivot(smb_font.CCD_PIVOT_LC);
         }
         this.txt_bns_cond.SetTextSize(28);
         this.txt_bns_cond.SetTextFieldWidth(1055);
         this.txt_bns_cond.SetTextFit(true);
         this.txt_bns_cond.SetTextColor(smb_font.CCD_COLOR_WHITE);
      }
   }
}

