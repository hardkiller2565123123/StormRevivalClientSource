package script.net_card
{
   import ELoader.ExtendLoader;
   import flash.display.MovieClip;
   import flash.events.Event;
   import flash.events.ProgressEvent;
   import flash.external.*;
   import flash.net.URLRequest;
   import script.icon_rarity.nut_rarity;
   
   public class nut_card extends MovieClip
   {
      
      internal static var CCD_INFOCARD_STEP_OPEN_START:int = 0;
      
      internal static var CCD_INFOCARD_STEP_OPEN:int = 1;
      
      internal static var CCD_INFOCARD_STEP_OPEN_END:int = 2;
      
      internal static var CCD_INFOCARD_STEP_CLOSE_START:int = 3;
      
      internal static var CCD_INFOCARD_STEP_CLOSE:int = 4;
      
      internal static var CCD_INFOCARD_STEP_CLOSE_END:int = 5;
      
      internal static var CCD_INFOCARD_STEP_OPEN_ALWAYS:int = 6;
      
      internal static var CCD_INFOCARD_STEP_CLOSE_ALWAYS:int = 7;
      
      internal static var CCD_INFOCARD_STEP_WAIT:int = 8;
      
      internal static var CCD_INFOCARD_STEP_SET_IMAGE:int = 9;
      
      internal static var CCD_INFOCARD_REQUEST_NONE:int = 0;
      
      internal static var CCD_INFOCARD_REQUEST_OPEN:int = 1;
      
      internal static var CCD_INFOCARD_REQUEST_CLOSE:int = 2;
      
      public static var CCD_INFOCARD_INVALID_SKIN_NO:uint = 999;
      
      public var SetClosed:Function;
      
      public var m_step:int;
      
      public var m_type:int;
      
      public var m_isLoadEnd:Boolean;
      
      public var m_isLoadRequest:Boolean;
      
      public var m_isAlwaysOpen:Boolean;
      
      public var m_skinOpenNo:int;
      
      public var m_isLoadEndSkin:Boolean;
      
      public var m_isLoadSkinRequest:Boolean;
      
      public var m_isRequest:Boolean;
      
      public var m_isOutfront:Boolean = false;
      
      public var m_beforeImageName:String = null;
      
      public var m_beforeSkinNo:int = -1;
      
      public var m_rarity:int = -1;
      
      public var m_name1:String = null;
      
      public var m_name2:String = null;
      
      public var m_BP:int = -1;
      
      public var m_rank:int = -1;
      
      public var m_className:String = null;
      
      public var m_UserId:String = null;
      
      public var m_region:String = null;
      
      public var m_isSetRequest:Boolean = false;
      
      public var m_imageReserv:String = null;
      
      public var m_skinReserv:int = 0;
      
      public var m_rarityReserv:int = 0;
      
      public var m_name1Reserv:String = null;
      
      public var m_name2Reserv:String = null;
      
      public var m_BPReserv:int = 0;
      
      public var m_rankReserv:int = 0;
      
      public var m_classNameReserv:String = null;
      
      public var m_UserIdReserv:String = null;
      
      public var m_regionReserv:String = null;
      
      public var m_isSetRequestReserv:Boolean = false;
      
      public var m_reservWaitCnt:int = 0;
      
      internal var card_front:MovieClip = null;
      
      private var my_loader:Array = new Array(2);
      
      private var m_loaderNo:int = 0;
      
      private var my_loaderSkin:Array = new Array(2);
      
      private var m_loaderSkinNo:int = 0;
      
      public function nut_card()
      {
         super();
         trace("nut_card constructor" + this.name);
         trace("nut_card constructor" + this.parent.name);
         this.card_front = getChildByName("all_card_front") as MovieClip;
         trace(this.card_front);
         trace(this.card_front.mc_eff00);
         this.card_front.mc_eff00.visible = false;
         trace(this.card_front.txt_userid);
         this.card_front.txt_userid.visible = false;
         trace(this.card_front.mc_card_title.txt_title00);
         this.card_front.mc_card_title.txt_title00.visible = false;
         trace(this.card_front.mc_card_title.txt_title01);
         this.card_front.mc_card_title.txt_title01.visible = false;
         trace(this.card_front.txt_region);
         this.card_front.txt_region.visible = false;
         trace(this.card_front.mc_rank_title.txt_rank_title);
         this.card_front.mc_rank_title.txt_rank_title.visible = false;
         trace(this.card_front.txt_bp);
         this.card_front.txt_bp.visible = false;
         trace(this.card_front.txt_bp_num);
         this.card_front.txt_bp_num.visible = false;
         trace(this.card_front.all_rank);
         this.card_front.all_rank.visible = false;
         trace(this.card_front.txt_rank);
         this.card_front.txt_rank.ChangeBitmapDraw();
         this.card_front.txt_rank.visible = false;
         trace(this.card_front.all_rarity);
         this.card_front.all_rarity.visible = false;
         trace(this.card_front.all_card_skin);
         this.card_front.all_card_skin.visible = false;
         trace(this.card_front.image_back);
         this.card_front.image_back.visible = false;
         trace("obj setting end");
         this.m_step = CCD_INFOCARD_STEP_CLOSE_ALWAYS;
         this.m_type = CCD_INFOCARD_REQUEST_NONE;
         this.m_isLoadEnd = false;
         this.m_isLoadRequest = false;
         this.m_isAlwaysOpen = false;
         this.m_skinOpenNo = -1;
         this.m_isLoadEndSkin = false;
         this.m_isLoadSkinRequest = false;
         this.m_isRequest = false;
         this.m_isSetRequest = false;
         this.m_beforeImageName = null;
         this.m_beforeSkinNo = -1;
         this.card_front.mc_card_title.txt_title00.cacheAsBitmap = true;
         this.card_front.mc_card_title.txt_title01.cacheAsBitmap = true;
         addEventListener(Event.ENTER_FRAME,this.onEnterFrameCtrl);
         trace("event end");
      }
      
      public function Initialize() : void
      {
         trace("nut_card Initialize");
      }
      
      public function onEnterFrameCtrl(param1:*) : void
      {
         var _loc4_:* = undefined;
         var _loc5_:* = undefined;
         var _loc6_:* = undefined;
         var _loc7_:* = undefined;
         if(this.m_isOutfront == true)
         {
            return;
         }
         var _loc2_:MovieClip = null;
         var _loc3_:int = 0;
         this.m_isRequest = false;
         switch(this.m_step)
         {
            case CCD_INFOCARD_STEP_OPEN_START:
               if(this.m_isLoadEnd == this.m_isLoadRequest && this.m_isLoadEndSkin == this.m_isLoadSkinRequest)
               {
                  gotoAndPlay("start");
                  this.m_step = CCD_INFOCARD_STEP_OPEN;
                  trace("to CCD_INFOCARD_STEP_OPEN");
               }
               break;
            case CCD_INFOCARD_STEP_OPEN:
               if(currentFrameLabel == "open")
               {
                  trace("to CCD_INFOCARD_STEP_OPEN_END");
                  this.card_front.image_back.visible = true;
                  this.m_step = CCD_INFOCARD_STEP_SET_IMAGE;
               }
               break;
            case CCD_INFOCARD_STEP_SET_IMAGE:
               this.SetRequestCardInfo();
               if(this.m_isSetRequest)
               {
                  this.m_isSetRequest = false;
               }
               if(this.my_loader[this.m_loaderNo])
               {
                  this.card_front = getChildByName("all_card_front") as MovieClip;
                  _loc4_ = this.card_front.getChildByName("dmy_images") as MovieClip;
                  trace("CCD_INFOCARD_STEP_SET_IMAGE image set ready " + _loc4_);
                  if(_loc4_ != null)
                  {
                     trace("image set complete");
                     _loc4_.addChild(this.my_loader[this.m_loaderNo]);
                     this.my_loader[this.m_loaderNo].SetPivot(ExtendLoader.CCD_PIVOT_CENTER_CENTER);
                  }
               }
               if(this.m_skinOpenNo != -1 && Boolean(this.my_loaderSkin[this.m_loaderSkinNo]))
               {
                  this.card_front = getChildByName("all_card_front") as MovieClip;
                  _loc5_ = this.card_front.all_card_skin.getChildByName("dmy_skin") as MovieClip;
                  trace("CCD_INFOCARD_STEP_SET_IMAGE image set ready " + _loc5_);
                  if(_loc5_ != null)
                  {
                     trace("image set complete");
                     _loc5_.addChild(this.my_loaderSkin[this.m_loaderSkinNo]);
                     this.my_loaderSkin[this.m_loaderSkinNo].SetPivot(ExtendLoader.CCD_PIVOT_CENTER_CENTER);
                  }
                  _loc2_ = this.card_front.getChildByName("all_card_skin") as MovieClip;
                  _loc2_.visible = true;
                  _loc3_ = this.m_skinOpenNo % 5 + 2;
                  if(_loc3_ > 5)
                  {
                     _loc3_ -= 5;
                  }
                  _loc2_.gotoAndStop("eff" + _loc3_);
                  _loc2_.gotoAndStop("eff" + (this.m_skinOpenNo % 5 + 1));
                  this.m_skinOpenNo = -1;
               }
               this.m_isLoadEnd = false;
               this.m_isLoadRequest = false;
               this.m_isLoadEndSkin = false;
               this.m_isLoadSkinRequest = false;
               this.m_step = CCD_INFOCARD_STEP_OPEN_END;
               this.m_type = CCD_INFOCARD_REQUEST_NONE;
               break;
            case CCD_INFOCARD_STEP_OPEN_END:
               if(this.m_isSetRequestReserv)
               {
                  this.RequestSetCardInfo(this.m_imageReserv,this.m_rarityReserv,this.m_skinReserv,this.m_name1Reserv,this.m_name2Reserv,this.m_BPReserv,this.m_rankReserv,this.m_classNameReserv,this.m_UserIdReserv,this.m_regionReserv,0);
                  this.m_isSetRequestReserv = false;
               }
               break;
            case CCD_INFOCARD_STEP_CLOSE_START:
               gotoAndPlay("close");
               this.m_step = CCD_INFOCARD_STEP_CLOSE;
               trace("CCD_INFOCARD_STEP_CLOSE_START");
               break;
            case CCD_INFOCARD_STEP_CLOSE:
               trace("m_isLoadEnd : " + this.m_isLoadEnd);
               trace("m_isLoadRequest : " + this.m_isLoadRequest);
               trace("m_isLoadEndSkin : " + this.m_isLoadEndSkin);
               trace("m_isLoadSkinRequest : " + this.m_isLoadSkinRequest);
               trace("m_type : " + this.m_type);
               if(this.m_isLoadEnd == this.m_isLoadRequest && this.m_isLoadEndSkin == this.m_isLoadSkinRequest && currentFrameLabel == "next" && this.m_type == CCD_INFOCARD_REQUEST_OPEN && (!this.m_isSetRequestReserv && !this.m_isSetRequest))
               {
                  gotoAndPlay("open");
                  this.card_front.image_back.visible = true;
                  this.m_step = CCD_INFOCARD_STEP_SET_IMAGE;
                  trace("to CCD_INFOCARD_STEP_SET_IMAGE");
               }
               else if(currentFrameLabel == "end")
               {
                  this.m_step = CCD_INFOCARD_STEP_CLOSE_END;
                  if(this.m_type != CCD_INFOCARD_REQUEST_OPEN)
                  {
                     this.m_type = CCD_INFOCARD_REQUEST_NONE;
                     trace("to CCD_INFOCARD_STEP_CLOSE_END");
                     trace("m_type : " + this.m_type);
                  }
               }
               break;
            case CCD_INFOCARD_STEP_CLOSE_END:
               if(this.m_reservWaitCnt > 0)
               {
                  if(this.m_isSetRequestReserv)
                  {
                     this.RequestSetCardInfo(this.m_imageReserv,this.m_rarityReserv,this.m_skinReserv,this.m_name1Reserv,this.m_name2Reserv,this.m_BPReserv,this.m_rankReserv,this.m_classNameReserv,this.m_UserIdReserv,this.m_regionReserv,0);
                     this.m_isSetRequestReserv = false;
                  }
                  --this.m_reservWaitCnt;
               }
               if(this.m_type == CCD_INFOCARD_REQUEST_OPEN && this.m_isLoadEnd == this.m_isLoadRequest && this.m_isLoadEndSkin == this.m_isLoadSkinRequest && this.m_reservWaitCnt <= 0)
               {
                  this.m_step = CCD_INFOCARD_STEP_OPEN_START;
                  trace("to CCD_INFOCARD_STEP_OPEN_START");
               }
               break;
            case CCD_INFOCARD_STEP_OPEN_ALWAYS:
               if(this.m_isLoadEnd == this.m_isLoadRequest && this.m_isLoadEndSkin == this.m_isLoadSkinRequest)
               {
                  this.card_front.visible = true;
                  gotoAndStop("loop");
                  if(this.m_isLoadEnd)
                  {
                     this.card_front = getChildByName("all_card_front") as MovieClip;
                     _loc6_ = this.card_front.getChildByName("dmy_images") as MovieClip;
                     trace("CCD_INFOCARD_STEP_OPEN_ALWAYS image set ready " + _loc6_);
                     if(_loc6_ != null)
                     {
                        trace("image set complete");
                        _loc6_.addChild(this.my_loader[this.m_loaderNo]);
                        this.my_loader[this.m_loaderNo].SetPivot(ExtendLoader.CCD_PIVOT_CENTER_CENTER);
                     }
                     this.m_isLoadEnd = false;
                     this.m_isLoadRequest = false;
                  }
                  if(this.m_isLoadEndSkin)
                  {
                     this.card_front = getChildByName("all_card_front") as MovieClip;
                     _loc7_ = this.card_front.all_card_skin.getChildByName("dmy_skin") as MovieClip;
                     trace("CCD_INFOCARD_STEP_OPEN_ALWAYS image set ready " + _loc7_);
                     if(_loc7_ != null)
                     {
                        trace("image set complete");
                        _loc7_.addChild(this.my_loaderSkin[this.m_loaderSkinNo]);
                        this.my_loaderSkin[this.m_loaderSkinNo].SetPivot(ExtendLoader.CCD_PIVOT_CENTER_CENTER);
                     }
                     _loc2_ = this.card_front.getChildByName("all_card_skin") as MovieClip;
                     _loc2_.visible = true;
                     _loc3_ = this.m_skinOpenNo % 5 + 2;
                     if(_loc3_ > 5)
                     {
                        _loc3_ -= 5;
                     }
                     _loc2_.gotoAndStop("eff" + _loc3_);
                     _loc2_.gotoAndStop("eff" + (this.m_skinOpenNo % 5 + 1));
                     this.m_isLoadEndSkin = false;
                     this.m_isLoadSkinRequest = false;
                  }
                  this.m_type = CCD_INFOCARD_REQUEST_NONE;
                  this.m_step = CCD_INFOCARD_STEP_WAIT;
               }
               break;
            case CCD_INFOCARD_STEP_CLOSE_ALWAYS:
               if(!this.m_isAlwaysOpen)
               {
                  gotoAndStop("end");
                  this.m_step = CCD_INFOCARD_STEP_CLOSE_END;
               }
               break;
            case CCD_INFOCARD_STEP_WAIT:
               if(this.m_isSetRequestReserv)
               {
                  this.RequestSetCardInfo(this.m_imageReserv,this.m_rarityReserv,this.m_skinReserv,this.m_name1Reserv,this.m_name2Reserv,this.m_BPReserv,this.m_rankReserv,this.m_classNameReserv,this.m_UserIdReserv,this.m_regionReserv,0);
                  this.m_isSetRequestReserv = false;
               }
         }
      }
      
      public function SetAlwaysOpen(param1:Boolean) : void
      {
         this.m_isAlwaysOpen = param1;
         if(this.m_isAlwaysOpen)
         {
            gotoAndStop("loop");
            this.m_step = CCD_INFOCARD_STEP_OPEN_ALWAYS;
            this.card_front.visible = false;
         }
         else
         {
            this.card_front.visible = true;
         }
         trace("SetAlwaysOpen : " + param1);
      }
      
      public function open() : void
      {
         if(this.m_isRequest)
         {
            trace("already open request on this frame");
            return;
         }
         trace("step : " + this.m_step);
         if(this.m_isAlwaysOpen)
         {
            this.m_step = CCD_INFOCARD_STEP_OPEN_ALWAYS;
         }
         else if(this.m_isSetRequestReserv || this.m_isSetRequest)
         {
            if(this.m_step != CCD_INFOCARD_STEP_CLOSE_START && this.m_step != CCD_INFOCARD_STEP_CLOSE && this.m_step != CCD_INFOCARD_STEP_CLOSE_END)
            {
               this.m_step = CCD_INFOCARD_STEP_CLOSE_START;
            }
         }
         else if(this.m_step == CCD_INFOCARD_STEP_CLOSE_END)
         {
            this.m_step = CCD_INFOCARD_STEP_OPEN_START;
         }
         else if(this.m_type != CCD_INFOCARD_REQUEST_CLOSE)
         {
            this.m_step = CCD_INFOCARD_STEP_CLOSE_START;
            trace("to CCD_INFOCARD_STEP_CLOSE_START");
         }
         else
         {
            trace("m_step : " + this.m_step);
            trace("m_type : " + this.m_type);
         }
         this.m_type = CCD_INFOCARD_REQUEST_OPEN;
         this.m_isRequest = true;
      }
      
      public function close(param1:Boolean = false) : void
      {
         this.m_isLoadEnd = false;
         this.m_isLoadEndSkin = false;
         if(this.m_step >= CCD_INFOCARD_STEP_CLOSE_START && this.m_step <= CCD_INFOCARD_STEP_CLOSE_END)
         {
            this.m_type = CCD_INFOCARD_REQUEST_CLOSE;
         }
         else
         {
            if(param1)
            {
               this.m_step = CCD_INFOCARD_STEP_CLOSE_ALWAYS;
            }
            else
            {
               this.m_step = CCD_INFOCARD_STEP_CLOSE_START;
            }
            this.m_type = CCD_INFOCARD_REQUEST_CLOSE;
         }
      }
      
      public function change() : void
      {
         gotoAndPlay("chage");
      }
      
      public function out_front() : void
      {
         this.m_isOutfront = true;
         gotoAndPlay("out_front");
      }
      
      public function setImage(param1:String) : void
      {
         if(!this.m_beforeImageName && this.m_beforeImageName == param1)
         {
            return;
         }
         this.m_loaderNo = 1 - this.m_loaderNo;
         this.clearImage();
         this.m_isLoadEnd = false;
         this.m_isLoadRequest = true;
         trace(param1);
         var _loc2_:URLRequest = new URLRequest(param1);
         this.my_loader[this.m_loaderNo].load(_loc2_);
         addEventListener(Event.ENTER_FRAME,this.loadingCheckImage);
         this.m_beforeImageName = param1;
         this.open();
      }
      
      public function clearImage() : void
      {
         if(this.my_loader[this.m_loaderNo])
         {
            this.my_loader[this.m_loaderNo].unload();
            trace("unload Image");
            this.my_loader[this.m_loaderNo] = null;
            this.my_loader[this.m_loaderNo] = new ExtendLoader();
         }
         else
         {
            this.my_loader[this.m_loaderNo] = new ExtendLoader();
         }
         this.m_beforeImageName = null;
      }
      
      private function attachImage(param1:Event) : void
      {
         trace("loadComplete");
         this.m_isLoadEnd = true;
         this.my_loader[this.m_loaderNo].contentLoaderInfo.removeEventListener(ProgressEvent.PROGRESS,this.onLoadProgress);
         this.my_loader[this.m_loaderNo].contentLoaderInfo.removeEventListener(Event.COMPLETE,this.attachImage);
      }
      
      private function onLoadProgress(param1:ProgressEvent) : void
      {
         var _loc2_:uint = Math.round(100 * (param1.bytesLoaded / param1.bytesTotal));
         trace("The sound is " + _loc2_ + "% loaded.");
      }
      
      private function loadingCheckImage(param1:*) : void
      {
         if(this.my_loader[this.m_loaderNo].IsLoadedAll())
         {
            trace("loadComplete");
            this.m_isLoadEnd = true;
            removeEventListener(Event.ENTER_FRAME,this.loadingCheckImage);
         }
      }
      
      public function setRarity(param1:int) : void
      {
         var _loc2_:nut_rarity = this.card_front.getChildByName("all_rarity") as nut_rarity;
         trace("setRarity : " + param1 + " : " + _loc2_);
         _loc2_.visible = true;
         switch(param1)
         {
            case 0:
               _loc2_.gotoAndStop("n");
               break;
            case 1:
               _loc2_.gotoAndStop("r");
               break;
            case 2:
               _loc2_.gotoAndStop("sr");
               break;
            case 3:
               _loc2_.gotoAndStop("ur");
               break;
            case 4:
               _loc2_.gotoAndStop("sc");
         }
      }
      
      public function setRarityRequest(param1:int) : void
      {
         this.m_rarity = param1;
      }
      
      public function setName(param1:int, param2:String) : void
      {
         var _loc3_:MovieClip = this.card_front.mc_card_title.getChildByName("txt_title0" + param1) as MovieClip;
         _loc3_.visible = true;
         _loc3_.SetText(param2);
         _loc3_.ChangeBitmapDraw();
         _loc3_.UpdateBitmap();
      }
      
      public function setSkin(param1:uint) : void
      {
         var _loc2_:MovieClip = this.card_front.getChildByName("all_card_skin") as MovieClip;
         _loc2_.visible = true;
         var _loc3_:int = param1 % 5 + 2;
         if(_loc3_ > 5)
         {
            _loc3_ -= 5;
         }
         _loc2_.gotoAndStop("eff" + _loc3_);
         _loc2_.gotoAndStop("eff" + (param1 % 5 + 1));
         _loc2_.visible = true;
         trace("setSkin : ");
      }
      
      public function setSkinOpen(param1:uint) : void
      {
         trace("setSkinOpen m_beforeSkinNo : " + this.m_beforeSkinNo);
         trace("                  TargetNo : " + param1);
         if(this.m_beforeSkinNo == param1)
         {
            return;
         }
         if(param1 == CCD_INFOCARD_INVALID_SKIN_NO)
         {
            this.m_type = CCD_INFOCARD_REQUEST_NONE;
            return;
         }
         this.m_loaderSkinNo = 1 - this.m_loaderSkinNo;
         this.m_isLoadEndSkin = false;
         this.m_isLoadSkinRequest = true;
         this.clearSkin();
         this.m_skinOpenNo = param1;
         trace("no : " + param1 + "   ../net_card/tex_skin/card_skin" + (param1 % 5 + 1) + "_" + (int(param1 / 5) + 1) + ".xfbin");
         var _loc2_:URLRequest = new URLRequest("../net_card/tex_skin/card_skin" + (param1 % 5 + 1) + "_" + (int(param1 / 5) + 1) + ".xfbin");
         this.my_loaderSkin[this.m_loaderSkinNo].load(_loc2_);
         addEventListener(Event.ENTER_FRAME,this.loadingCheckSkin);
         var _loc3_:MovieClip = this.card_front.getChildByName("all_card_skin") as MovieClip;
         _loc3_.visible = true;
         this.m_beforeSkinNo = param1;
         this.open();
      }
      
      public function clearSkin() : void
      {
         if(this.my_loaderSkin[this.m_loaderSkinNo])
         {
            this.my_loaderSkin[this.m_loaderSkinNo].unload();
            trace("unload skin");
            this.my_loaderSkin[this.m_loaderSkinNo] = null;
            this.my_loaderSkin[this.m_loaderSkinNo] = new ExtendLoader();
         }
         else
         {
            this.my_loaderSkin[this.m_loaderSkinNo] = new ExtendLoader();
         }
         this.m_beforeSkinNo = -1;
      }
      
      private function attachSkin(param1:Event) : void
      {
         trace("loadComplete");
         this.m_isLoadEndSkin = true;
         this.my_loaderSkin[this.m_loaderSkinNo].contentLoaderInfo.removeEventListener(ProgressEvent.PROGRESS,this.onLoadProgressSkin);
         this.my_loaderSkin[this.m_loaderSkinNo].contentLoaderInfo.removeEventListener(Event.COMPLETE,this.attachSkin);
      }
      
      private function onLoadProgressSkin(param1:ProgressEvent) : void
      {
         var _loc2_:uint = Math.round(100 * (param1.bytesLoaded / param1.bytesTotal));
         trace("The sound is " + _loc2_ + "% loaded.");
      }
      
      private function loadingCheckSkin(param1:*) : void
      {
         if(this.my_loaderSkin[this.m_loaderSkinNo].IsLoadedAll())
         {
            trace("loadComplete");
            this.m_isLoadEndSkin = true;
            removeEventListener(Event.ENTER_FRAME,this.loadingCheckSkin);
         }
      }
      
      public function setUserId(param1:String) : void
      {
         trace("userId:" + param1);
         var _loc2_:MovieClip = this.card_front.getChildByName("txt_userid") as MovieClip;
         _loc2_.visible = true;
         _loc2_.SetText(param1);
         _loc2_.ChangeBitmapDraw();
         _loc2_.UpdateBitmap();
      }
      
      public function setRegion(param1:String) : void
      {
         var _loc2_:MovieClip = this.card_front.getChildByName("txt_region") as MovieClip;
         _loc2_.visible = true;
         _loc2_.SetText(param1);
         _loc2_.ChangeBitmapDraw();
         _loc2_.UpdateBitmap();
      }
      
      public function setBP(param1:int) : void
      {
         trace("setBP " + this.name);
         trace("setBP" + this.parent.name);
         trace("bp:" + param1);
         var _loc2_:MovieClip = null;
         _loc2_ = this.card_front.getChildByName("txt_bp") as MovieClip;
         if(_loc2_)
         {
            _loc2_.visible = true;
            _loc2_.SetText(String(ExternalInterface.call("MessageConvert","networkmode_406")));
            _loc2_.ChangeBitmapDraw();
            _loc2_.UpdateBitmap();
         }
         else
         {
            trace("not found txt_bp");
         }
         _loc2_ = this.card_front.getChildByName("txt_bp_num") as MovieClip;
         if(_loc2_)
         {
            _loc2_.visible = true;
            _loc2_.SetText(String(param1));
            _loc2_.ChangeBitmapDraw();
            _loc2_.UpdateBitmap();
         }
         else
         {
            trace("not found txt_bp_num");
         }
      }
      
      public function setRank(param1:int) : void
      {
         var _loc2_:MovieClip = this.card_front.getChildByName("all_rank") as MovieClip;
         _loc2_.visible = true;
         if(param1 >= 39)
         {
            _loc2_.gotoAndStop("rankmax");
            this.card_front.txt_rank.visible = false;
         }
         else
         {
            this.card_front.txt_rank.visible = true;
            this.card_front.txt_rank.SetText(String("" + param1));
            _loc2_.gotoAndStop("rank0");
         }
      }
      
      public function setClass(param1:String) : void
      {
         var _loc2_:MovieClip = this.card_front.mc_rank_title.getChildByName("txt_rank_title") as MovieClip;
         _loc2_.visible = true;
         _loc2_.SetText(param1);
         _loc2_.ChangeBitmapDraw();
         _loc2_.UpdateBitmap();
      }
      
      public function setCardInfo(param1:String, param2:int, param3:uint, param4:String, param5:String, param6:int, param7:int, param8:String, param9:String, param10:String, param11:int) : void
      {
         this.setImage(param1);
         this.setRarity(param2);
         this.setSkinOpen(param3);
         this.setName(0,param4);
         this.setName(1,param5);
         this.setBP(param6);
         this.setRank(param7);
         this.setClass(param8);
         this.setUserId(param9);
         this.setRegion(param10);
         this.m_isSetRequest = false;
      }
      
      public function RequestSetCardInfo(param1:String, param2:int, param3:uint, param4:String, param5:String, param6:int, param7:int, param8:String, param9:String, param10:String, param11:int) : void
      {
         trace("######### RequestSetCardInfo m_step : " + this.m_step);
         trace("#########                    m_type : " + this.m_type);
         if(this.m_step == CCD_INFOCARD_STEP_OPEN_END || this.m_step == CCD_INFOCARD_STEP_WAIT || this.m_step == CCD_INFOCARD_STEP_CLOSE_END && this.m_type == CCD_INFOCARD_REQUEST_NONE || this.m_step == CCD_INFOCARD_STEP_CLOSE_ALWAYS || this.m_step == CCD_INFOCARD_STEP_CLOSE_END && this.m_reservWaitCnt > 0)
         {
            this.setImage(param1);
            this.m_rarity = param2;
            this.setSkinOpen(param3);
            this.m_name1 = param4;
            this.m_name2 = param5;
            this.m_BP = param6;
            this.m_rank = param7;
            this.m_className = param8;
            this.m_UserId = param9;
            this.m_region = param10;
            this.m_isSetRequest = true;
            this.m_isSetRequestReserv = false;
            this.m_reservWaitCnt = 0;
         }
         else
         {
            this.m_imageReserv = param1;
            this.m_skinReserv = param3;
            this.m_rarityReserv = param2;
            this.m_name1Reserv = param4;
            this.m_name2Reserv = param5;
            this.m_BPReserv = param6;
            this.m_rankReserv = param7;
            this.m_classNameReserv = param8;
            this.m_UserIdReserv = param9;
            this.m_regionReserv = param10;
            this.m_isSetRequestReserv = true;
            this.m_reservWaitCnt = 15;
         }
      }
      
      public function SetRequestCardInfo() : void
      {
         if(this.m_rarity >= 0)
         {
            this.setRarity(this.m_rarity);
         }
         if(this.m_name1 != null)
         {
            this.setName(0,this.m_name1);
         }
         if(this.m_name2 != null)
         {
            this.setName(1,this.m_name2);
         }
         if(this.m_BP >= 0)
         {
            this.setBP(this.m_BP);
         }
         if(this.m_rank >= 0)
         {
            this.setRank(this.m_rank);
         }
         if(this.m_className != null)
         {
            this.setClass(this.m_className);
         }
         if(this.m_UserId != null)
         {
            this.setUserId(this.m_UserId);
         }
         if(this.m_region != null)
         {
            this.setRegion(this.m_region);
         }
      }
   }
}

