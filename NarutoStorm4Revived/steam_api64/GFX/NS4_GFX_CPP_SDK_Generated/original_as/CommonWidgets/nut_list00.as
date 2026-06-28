package script.collect_top
{
   import flash.display.MovieClip;
   import flash.geom.Point;
   import script.xcmn_font.smb_font;
   import script.xcmn_list_brt.all_list2_off;
   import script.xcmn_list_brt.ll_list2_on;
   import script.xcmn_menu.nut_cursor_m;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol1")]
   public dynamic class nut_list00 extends MovieClip
   {
      
      public var all_cursor_m:nut_cursor_m;
      
      public var mc_plate_off:all_list2_off;
      
      public var mc_plate_on:ll_list2_on;
      
      public var txt_list:smb_font;
      
      public var pos:Point;
      
      public function nut_list00()
      {
         super();
         addFrameScript(0,this.frame1,41,this.frame42,42,this.frame43,43,this.frame44);
      }
      
      internal function frame1() : *
      {
         gotoAndPlay(1);
         this.txt_list.SetTextFit(true);
         this.txt_list.SetTextFieldWidth(780);
         if(this.txt_list.IsArabic() == true)
         {
            this.txt_list.SetTextPivot(smb_font.CCD_PIVOT_RC);
            this.pos = new Point();
            this.txt_list.GetTextPos(this.pos);
            if(this.pos.x < 0)
            {
               this.txt_list.SetTextPos(-this.pos.x,this.pos.y);
            }
            this.mc_plate_on.scaleX = -1;
         }
         else
         {
            this.txt_list.SetTextPivot(smb_font.CCD_PIVOT_LC);
         }
         this.txt_list.SetTextColor(16771961);
         this.txt_list.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_list.SetTextSize(33);
      }
      
      internal function frame42() : *
      {
         gotoAndPlay("loop");
      }
      
      internal function frame43() : *
      {
         stop();
         this.txt_list.SetTextFit(true);
         this.txt_list.SetTextFieldWidth(780);
         if(this.txt_list.IsArabic() == true)
         {
            this.txt_list.SetTextPivot(smb_font.CCD_PIVOT_RC);
            this.txt_list.GetTextPos(this.pos);
            if(this.pos.x < 0)
            {
               this.txt_list.SetTextPos(-this.pos.x,this.pos.y);
            }
            this.mc_plate_on.scaleX = -1;
         }
         else
         {
            this.txt_list.SetTextPivot(smb_font.CCD_PIVOT_LC);
         }
         this.txt_list.SetTextColor(16771961);
         this.txt_list.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_list.SetTextSize(33);
      }
      
      internal function frame44() : *
      {
         stop();
         this.txt_list.SetTextFit(true);
         this.txt_list.SetTextFieldWidth(780);
         if(this.txt_list.IsArabic() == true)
         {
            this.txt_list.SetTextPivot(smb_font.CCD_PIVOT_RC);
            this.txt_list.GetTextPos(this.pos);
            if(this.pos.x < 0)
            {
               this.txt_list.SetTextPos(-this.pos.x,this.pos.y);
            }
            this.mc_plate_off.scaleX = -1;
         }
         else
         {
            this.txt_list.SetTextPivot(smb_font.CCD_PIVOT_LC);
         }
         this.txt_list.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_list.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_list.SetTextSize(33);
      }
   }
}

