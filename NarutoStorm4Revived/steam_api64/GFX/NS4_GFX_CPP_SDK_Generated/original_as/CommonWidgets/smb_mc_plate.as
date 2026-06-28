package script.collect_skin
{
   import ELoader.ExtendLoader;
   import flash.display.MovieClip;
   import flash.events.Event;
   import flash.net.URLRequest;
   import script.icon_confirm.nut_conf_s;
   import script.icon_new.nut_new;
   import script.icon_rarity.nut_rarity;
   import script.xcmn_font.smb_font;
   import script.xcmn_menu.nut_frame_1;
   import script.xcmn_tex00.nut_tex00;
   import script.xct_deco2.nut_deco2;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol4")]
   public class smb_mc_plate extends MovieClip
   {
      
      public var all_deco2:nut_deco2;
      
      public var dmy_skin:nut_tex00;
      
      public var mc_conf_s:nut_conf_s;
      
      public var mc_new:nut_new;
      
      public var mc_rarity:nut_rarity;
      
      public var mc_sel:nut_frame_1;
      
      public var txt_num:smb_font;
      
      public var setNo:int = 1;
      
      private var my_loader:ExtendLoader = null;
      
      public function smb_mc_plate()
      {
         super();
         addFrameScript(0,this.frame1,1,this.frame2,2,this.frame3,3,this.frame4);
      }
      
      public function setImage(param1:int) : void
      {
         var _loc2_:* = getChildByName("dmy_skin") as MovieClip;
         if(this.my_loader != null)
         {
            if(_loc2_ != null && Boolean(_loc2_.contains(this.my_loader)))
            {
               _loc2_.removeChild(this.my_loader);
            }
            this.my_loader = null;
         }
         this.my_loader = new ExtendLoader();
         trace("filename ../net_card/tex_skin_s/card_skin_s" + (param1 % 5 + 1) + "_" + (int(param1 / 5) + 1) + ".xfbin");
         var _loc3_:URLRequest = new URLRequest("../net_card/tex_skin_s/card_skin_s" + (param1 % 5 + 1) + "_" + (int(param1 / 5) + 1) + ".xfbin");
         this.my_loader.load(_loc3_);
         if(_loc2_ != null)
         {
            this.my_loader.SetPivot(ExtendLoader.CCD_PIVOT_CENTER_CENTER);
            _loc2_.addChild(this.my_loader);
         }
         addEventListener(Event.ENTER_FRAME,this.onEnterFrameCtrl);
         var _loc4_:int = param1 % 5 + 2;
         if(_loc4_ > 5)
         {
            _loc4_ = 1;
         }
         this.setNo = param1 % 5 + 1;
      }
      
      public function onEnterFrameCtrl(param1:*) : void
      {
         var _loc2_:* = undefined;
         if(this.my_loader != null && this.my_loader.IsLoadedAll())
         {
            trace("loadComplete skin image");
            _loc2_ = getChildByName("dmy_skin") as MovieClip;
            if(_loc2_ != null)
            {
               this.my_loader.SetPivot(ExtendLoader.CCD_PIVOT_CENTER_CENTER);
               if(_loc2_.contains(this.my_loader) == false)
               {
                  _loc2_.addChild(this.my_loader);
               }
            }
            removeEventListener(Event.ENTER_FRAME,this.onEnterFrameCtrl);
         }
      }
      
      public function clearImage() : void
      {
         if(this.my_loader != null)
         {
            this.my_loader.unload();
         }
      }
      
      internal function frame1() : *
      {
         this.stop();
         this.txt_num.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_num.SetTextSize(28);
         this.txt_num.SetTextColor(smb_font.CCD_COLOR_BLACK);
      }
      
      internal function frame2() : *
      {
         this.txt_num.SetTextColor(smb_font.CCD_COLOR_WHITE);
      }
      
      internal function frame3() : *
      {
         this.txt_num.SetTextColor(smb_font.CCD_COLOR_BLACK);
      }
      
      internal function frame4() : *
      {
         this.txt_num.SetTextColor(11315836);
      }
   }
}

