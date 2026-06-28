package shop_cmn_brt_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   import script.xcmn_list_brt.all_list2_off;
   import script.xcmn_list_brt.ll_list2_on;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol8")]
   public dynamic class smb_topbar_on_8 extends MovieClip
   {
      
      public var mc_plate_off:all_list2_off;
      
      public var mc_plate_on:ll_list2_on;
      
      public var txt_topbar:smb_font;
      
      public function smb_topbar_on_8()
      {
         super();
         addFrameScript(0,this.frame1,42,this.frame43,43,this.frame44);
      }
      
      internal function frame1() : *
      {
         gotoAndPlay(1);
         this.txt_topbar.SetTextFit(true);
         this.txt_topbar.SetTextFieldWidth(780);
         if(this.txt_topbar.IsArabic() == true)
         {
            this.txt_topbar.SetTextPivot(smb_font.CCD_PIVOT_RC);
            this.txt_topbar.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
            this.txt_topbar.SetTextPos(this.mc_plate_on.x * 2 + 393,0);
            this.mc_plate_on.scaleX = -1;
         }
         else
         {
            this.txt_topbar.SetTextPivot(smb_font.CCD_PIVOT_LC);
         }
         this.txt_topbar.SetTextColor(16771175);
         this.txt_topbar.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_topbar.SetTextSize(33);
      }
      
      internal function frame43() : *
      {
         gotoAndPlay("loop");
      }
      
      internal function frame44() : *
      {
         this.stop();
         this.txt_topbar.SetTextFit(true);
         this.txt_topbar.SetTextFieldWidth(780);
         if(this.txt_topbar.IsArabic() == true)
         {
            this.txt_topbar.SetTextPivot(smb_font.CCD_PIVOT_RC);
            this.txt_topbar.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
            this.txt_topbar.SetTextPos(this.mc_plate_off.x * 2 + 393,0);
            this.mc_plate_off.scaleX = -1;
         }
         else
         {
            this.txt_topbar.SetTextPivot(smb_font.CCD_PIVOT_LC);
         }
         this.txt_topbar.SetTextColor(13882323);
         this.txt_topbar.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_topbar.SetTextSize(33);
      }
   }
}

