package shop_cmn_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   import script.xcmn_list.all_list_off;
   import script.xcmn_list.all_list_on;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol9")]
   public dynamic class smb_topbar_on_9 extends MovieClip
   {
      
      public var mc_plate_off:all_list_off;
      
      public var mc_plate_on:all_list_on;
      
      public var txt_topbar:smb_font;
      
      public function smb_topbar_on_9()
      {
         super();
         addFrameScript(0,this.frame1,1,this.frame2);
      }
      
      internal function frame1() : *
      {
         this.stop();
         this.txt_topbar.SetTextFit(true);
         this.txt_topbar.SetTextFieldWidth(780);
         if(this.txt_topbar.IsArabic() == true)
         {
            this.txt_topbar.SetTextPivot(smb_font.CCD_PIVOT_RC);
            this.txt_topbar.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
            this.txt_topbar.SetTextPos(this.mc_plate_on.x * 2 + 70,0);
            this.mc_plate_on.scaleX = -1;
         }
         else
         {
            this.txt_topbar.SetTextPivot(smb_font.CCD_PIVOT_LC);
         }
         this.txt_topbar.SetTextColor(16771961);
         this.txt_topbar.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_topbar.SetTextSize(33);
      }
      
      internal function frame2() : *
      {
         this.stop();
         this.txt_topbar.SetTextFit(true);
         this.txt_topbar.SetTextFieldWidth(780);
         if(this.txt_topbar.IsArabic() == true)
         {
            this.txt_topbar.SetTextPivot(smb_font.CCD_PIVOT_RC);
            this.txt_topbar.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
            this.txt_topbar.SetTextPos(this.mc_plate_off.x * 2 + 70,0);
            this.mc_plate_off.scaleX = -1;
         }
         else
         {
            this.txt_topbar.SetTextPivot(smb_font.CCD_PIVOT_LC);
         }
         this.txt_topbar.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_topbar.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_topbar.SetTextSize(33);
      }
   }
}

