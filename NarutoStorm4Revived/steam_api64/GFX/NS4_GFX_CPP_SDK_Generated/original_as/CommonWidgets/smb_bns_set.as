package
{
   import flash.display.MovieClip;
   import script.icon_new.nut_new;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol18")]
   public dynamic class smb_bns_set extends MovieClip
   {
      
      public var mc_new:nut_new;
      
      public var txt_bns:smb_font;
      
      public var txt_bns_num:smb_font;
      
      public function smb_bns_set()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_bns_num.SetTextPivot(smb_font.CCD_PIVOT_RC);
         this.txt_bns_num.SetTextSize(30);
         this.txt_bns_num.SetTextFieldWidth(100);
         this.txt_bns_num.SetTextFit(true);
         this.txt_bns.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_bns.SetTextSize(30);
         this.txt_bns.SetTextFieldWidth(960);
         this.txt_bns.SetTextFit(true);
      }
   }
}

