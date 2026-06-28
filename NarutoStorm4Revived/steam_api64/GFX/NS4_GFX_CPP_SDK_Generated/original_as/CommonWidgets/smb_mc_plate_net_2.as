package script.collect_skin
{
   import ELoader.ExtendLoader;
   import flash.display.MovieClip;
   import flash.events.Event;
   import flash.net.URLRequest;
   import script.icon_new.nut_new;
   import script.xcmn_menu.nut_frame_1;
   import script.xcmn_tex00.nut_tex00;
   import script.xct_deco2.nut_deco2;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol8")]
   public class smb_mc_plate_net extends MovieClip
   {
      
      public var all_deco2:nut_deco2;
      
      public var dmy_img:nut_tex00;
      
      public var dmy_skin:nut_tex00;
      
      public var mc_lock:MovieClip;
      
      public var mc_new:nut_new;
      
      public var mc_sel:nut_frame_1;
      
      private var my_loaderSkin:ExtendLoader = new ExtendLoader();
      
      private var m_isLoadedSkn:Boolean = false;
      
      private var m_attachCntSkn:int = 0;
      
      private var my_loaderImage:ExtendLoader = new ExtendLoader();
      
      private var m_isLoadedImg:Boolean = false;
      
      private var m_attachCntImg:int = 0;
      
      public function smb_mc_plate_net()
      {
         super();
         addFrameScript(0,this.frame1,1,this.frame2);
      }
      
      public function setSkin(param1:int) : void
      {
         trace("filename ../net_card/tex_skin_s/card_skin_s" + (param1 % 5 + 1) + "_" + (int(param1 / 5) + 1) + ".xfbin");
         var _loc2_:URLRequest = new URLRequest("../net_card/tex_skin_s/card_skin_s" + (param1 % 5 + 1) + "_" + (int(param1 / 5) + 1) + ".xfbin");
         this.my_loaderSkin.load(_loc2_);
         this.my_loaderSkin.visible = false;
         addEventListener(Event.ENTER_FRAME,this.onLoadSkinCtrl);
         this.m_isLoadedSkn = false;
         this.m_attachCntSkn = 0;
      }
      
      public function onLoadSkinCtrl(param1:*) : void
      {
         var _loc2_:* = undefined;
         if(!this.m_isLoadedSkn)
         {
            if(this.my_loaderSkin.IsLoadedXfbin() && this.my_loaderSkin.IsLoadedAll())
            {
               this.m_isLoadedSkn = true;
            }
         }
         else
         {
            ++this.m_attachCntSkn;
            if(this.m_attachCntSkn > 2 && this.my_loaderSkin.visible == false)
            {
               _loc2_ = getChildByName("dmy_skin") as MovieClip;
               if(_loc2_ != null)
               {
                  this.my_loaderSkin.visible = true;
                  this.my_loaderSkin.SetPivot(ExtendLoader.CCD_PIVOT_CENTER_CENTER);
                  _loc2_.addChild(this.my_loaderSkin);
               }
               removeEventListener(Event.ENTER_FRAME,this.onLoadSkinCtrl);
            }
         }
      }
      
      public function clearSkin() : void
      {
         this.my_loaderSkin.unload();
      }
      
      public function setImage(param1:String) : void
      {
         trace("filename " + param1);
         var _loc2_:URLRequest = new URLRequest(param1);
         this.my_loaderImage.load(_loc2_);
         this.my_loaderImage.SetPivot(ExtendLoader.CCD_PIVOT_CENTER_CENTER);
         this.my_loaderImage.visible = false;
         addEventListener(Event.ENTER_FRAME,this.onLoadImageCtrl);
         this.m_isLoadedImg = false;
         this.m_attachCntImg = 0;
      }
      
      public function onLoadImageCtrl(param1:*) : void
      {
         var _loc2_:* = undefined;
         var _loc3_:* = undefined;
         if(!this.m_isLoadedImg)
         {
            if(this.my_loaderImage.IsLoadedXfbin() && this.my_loaderImage.IsLoadedAll())
            {
               this.m_isLoadedImg = true;
               this.my_loaderImage.SetPivot(ExtendLoader.CCD_PIVOT_CENTER_CENTER);
               _loc2_ = getChildByName("dmy_img") as MovieClip;
               if(_loc2_ != null)
               {
                  _loc2_.addChild(this.my_loaderImage);
               }
            }
         }
         else
         {
            ++this.m_attachCntImg;
            if(this.m_attachCntImg > 4 && this.my_loaderImage.visible == false)
            {
               _loc3_ = getChildByName("dmy_img") as MovieClip;
               if(_loc3_ != null)
               {
                  this.my_loaderImage.visible = true;
                  _loc2_.addChild(this.my_loaderImage);
               }
               removeEventListener(Event.ENTER_FRAME,this.onLoadImageCtrl);
            }
         }
      }
      
      public function clearImage() : void
      {
         this.my_loaderImage.unload();
      }
      
      internal function frame1() : *
      {
         this.stop();
      }
      
      internal function frame2() : *
      {
         this.stop();
      }
   }
}

